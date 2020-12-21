#include "httpClient.h"
#include "client.h"

namespace client {

void fail(beast::error_code ec, char const *what) {
  std::cerr << what << ": Error" << ec.message() << "\n";
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

http::response<http::string_body> SendRequestPlease(const std::string &host,
                                                    const std::string &port,
                                                    const http::request<http::string_body> &req) {

  // The io_context is required for all I/O
  net::io_context ioc;

  // These objects perform our I/O
  tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

  auto const results = resolver.resolve(host, port);

  stream.connect(results);

  http::write(stream, req);

  beast::flat_buffer buffer;

  http::response<http::string_body> res;

  http::read(stream, buffer, res);

  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};

  return res;
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

void Session::onWrite(beast::error_code ec, std::size_t bytes_transferred) {
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
  body_save = std::make_shared<std::string>(move(res_.body()));

  if (ec && ec != beast::errc::not_connected)
    return fail(ec, "shutdown");
}

http::response<http::string_body> HTTPClient::_sendRequest(const http::request<http::string_body> &request,
                                                           const std::string &host,
                                                           const std::string &port) {
//  s = std::make_shared<Session>(context_);
//  auto res = s->sendRequest(host, port, request);
//  context_.run();
  auto res = SendRequestPlease(host, port, request);
  return res;
}

http::response<http::string_body> RequestSender::sendRequest(const http::request<http::string_body> &request) const {
  return std::make_shared<HTTPClient>()->_sendRequest(request, host_, port_);
};

http::request<http::string_body> constructRequest(http::verb method,
                                                  const std::string &target,
                                                  std::string body) {
  http::request<http::string_body> req;
  req.method(method);
  req.target(target);
  req.body() = std::move(body);
  req.version(11);
  req.prepare_payload();
  return req;
}

ClientOut Client::update(int editorId, int docId, int cursorPos, const std::string &operations) {
  std::stringstream body;
  body << editorId << " " << docId << " " << cursorPos << " " << operations;
  return _getResponse(http::verb::post, "/edit", body.str());
}

ClientOut Client::connect(int editorId, int docId) {
  std::stringstream body;
  body << editorId << " " << docId;
  return _getResponse(http::verb::get, "/connect", body.str());
}

ClientOut Client::getTextDocument(int docId) {
  std::stringstream body;
  body << docId;
  return _getResponse(http::verb::get, "/getText", body.str());
}

ClientOut Client::create(int editorId, const std::string &documentName) {
  std::stringstream body;
  body << editorId << " " << documentName;
  return _getResponse(http::verb::post, "/create", body.str());
}

ClientOut Client::_getResponse(const http::verb &method, const std::string &target, std::string body) {
  ClientOut res;
  auto response = rs.sendRequest(constructRequest(method, target, std::move(body)));
  if (response.result() == http::status::ok)
    res.first = ClientErrors::success;
  else
    res.first = ClientErrors::failure;
  res.second = response.body();
  return res;
}
}

