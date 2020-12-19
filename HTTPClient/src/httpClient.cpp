#include "httpClient.h"

 #include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <utility>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


namespace client {
Session::Session(net::io_context &ioc) : resolver_ (net::make_strand(ioc)), stream_(net::make_strand(ioc)) {
}

http::response<http::string_body> Session::sendRequest(const std::string &host,
                                              const std::string &port,
                                              const http::request<http::string_body> &req) {
  req_ = req;
  resolver_.async_resolve(
      host,
      port,
      beast::bind_front_handler(
          &Session::onResolve,
          shared_from_this()));
  return res_;
}

void Session::onResolve(beast::error_code ec, const tcp::resolver::results_type &results) {
  if (ec)
    return fail(ec, "resolve");

  stream_.expires_after(std::chrono::seconds(30));

  stream_.async_connect(
      results,
      beast::bind_front_handler(
          &Session::onConnect,
          shared_from_this()));
}

void Session::onConnect(beast::error_code ec, const tcp::resolver::results_type::endpoint_type &) {
  if (ec)
    return fail(ec, "connect");

  stream_.expires_after(std::chrono::seconds(30));

  http::async_write(stream_, req_,
                    beast::bind_front_handler(
                        &Session::onWrite,
                        shared_from_this()));
}

void Session::onWrite(
    beast::error_code ec,
    std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec)
    return fail(ec, "write");

  http::async_read(stream_, buffer_, res_,
                   beast::bind_front_handler(
                       &Session::onRead,
                       shared_from_this()));
}

void Session::onRead(
    beast::error_code ec,
    std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec)
    return fail(ec, "read");

  stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    return fail(ec, "shutdown");
}

http::response<http::string_body> HTTPClient::sendRequest(const http::request<http::string_body> request,
                                              std::string host,
                                              std::string port) {
  s = std::make_shared<Session>(context_);
  auto res = s->sendRequest(host, port, request);
  context_.run();
  return res;
}

RequestSender::RequestSender(std::string host, std::string port) : host_ (std::move(host)), port_(std::move(port)) {}

http::response<http::string_body> RequestSender::sendRequest(const http::request<http::string_body> &request) const {
  return std::make_shared<HTTPClient>()->sendRequest(request, host_, port_);
}

http::request<http::string_body> constructRequest(http::verb method, const std::string &target, std::string body) {
  http::request<http::string_body> req;
  req.method(method);
  req.target(target);
  req.body() = std::move(body);
  req.version(11);
  req.prepare_payload();
  return req;
}

Client::Client(std::string host, std::string port) :rs(host, port) {}

ClientOut Client::update(int editorId, int docId, int cursorPos, const std::string &operations) {
  ClientOut res;
  std::stringstream body;
  body << editorId << " " << docId << " " << cursorPos << " " << operations;
  auto response = rs.sendRequest(constructRequest(http::verb::post, "/edit", body.str()));
  if (response.result() == http::status::ok)
    res.first = ClientErrors::success;
  else
    res.first = ClientErrors::failure;
  res.second = response.body();
  return res;
}

ClientOut Client::connect(int editorId, int docId) {
  ClientOut res;
  std::stringstream body;
  body << editorId << " " << docId;
  auto response = rs.sendRequest(constructRequest(http::verb::get, "/connect", body.str()));
  if (response.result() == http::status::ok)
    res.first = ClientErrors::success;
  else
    res.first = ClientErrors::failure;
  res.second = response.body();
  return res;
}
}
