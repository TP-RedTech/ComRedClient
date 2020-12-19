#ifndef HTTPCLIENT_INCLUDE_HTTPCLIENT_H
#define HTTPCLIENT_INCLUDE_HTTPCLIENT_H

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

namespace client {

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

void fail(beast::error_code ec, char const *what) {
  std::cerr << what << ": ERRORRRRR" << ec.message() << "\n";
}

class Session : public std::enable_shared_from_this<Session> {
public:
  explicit
  Session(net::io_context &ioc)
      : resolver_(net::make_strand(ioc)), stream_(net::make_strand(ioc)) {
  }

  http::response<http::string_body> sendRequest(const std::string &host,
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

  void onResolve(beast::error_code ec, const tcp::resolver::results_type &results) {
    if (ec)
      return fail(ec, "resolve");

    stream_.expires_after(std::chrono::seconds(30));

    stream_.async_connect(
        results,
        beast::bind_front_handler(
            &Session::onConnect,
            shared_from_this()));
  }

  void onConnect(beast::error_code ec, const tcp::resolver::results_type::endpoint_type &) {
    if (ec)
      return fail(ec, "connect");

    stream_.expires_after(std::chrono::seconds(30));

    http::async_write(stream_, req_,
                      beast::bind_front_handler(
                          &Session::onWrite,
                          shared_from_this()));
  }

  void onWrite(
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

  void onRead(
      beast::error_code ec,
      std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
      return fail(ec, "read");

    stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected)
      return fail(ec, "shutdown");
  }

private:
  tcp::resolver resolver_;
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  http::response<http::string_body> res_;
  http::request<http::string_body> req_;
};
class HTTPClient {
public:
  http::response<http::string_body> sendRequest(const http::request<http::string_body> request,
                                                std::string host,
                                                std::string port) {
    s = std::make_shared<Session>(context_);
    auto res = s->sendRequest(host, port, request);
    context_.run();
    return res;
  }

private:
  net::io_context context_;
  std::shared_ptr<Session> s;
};

class RequestSender {
public:
  RequestSender(std::string host, std::string port) : host_(std::move(host)), port_(std::move(port)) {}
  http::response<http::string_body> sendRequest(const http::request<http::string_body> &request) const {
    return std::make_shared<HTTPClient>()->sendRequest(request, host_, port_);
  }

public:
  std::string host_;
  std::string port_;
};

http::request<http::string_body> constructRequest(http::verb method, const std::string &target, std::string body) {
  http::request<http::string_body> req;
  req.method(method);
  req.target(target);
  req.body() = std::move(body);
  req.version(11);
  req.prepare_payload();
  return req;
}

enum class ClientErrors {
  success,
  failure
};

using ClientOut = std::pair<ClientErrors, std::string>;

class Client {
public:
  Client(std::string host, std::string port) : rs(host, port) {}

  ClientOut update(int editorId, int docId, int cursorPos, const std::string &operations) {
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

  ClientOut connect(int editorId, int docId) {
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

private:
  RequestSender rs;
};
}

#endif
