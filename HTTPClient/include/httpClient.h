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

void fail(beast::error_code ec, char const *what);

class FUCK {
public:
  std::string value;
  FUCK() {
    std::cout << "Createrd" << std::endl;
  }
};

class Session : public std::enable_shared_from_this<Session> {
public:
  explicit
  Session(net::io_context &ioc)
      : resolver_(net::make_strand(ioc)), stream_(net::make_strand(ioc)) {
  }

  http::response<http::string_body> sendRequest(const std::string &host,
                                                const std::string &port,
                                                const http::request<http::string_body> &req);

  void onResolve(beast::error_code ec, const tcp::resolver::results_type &results);

  void onConnect(beast::error_code ec, const tcp::resolver::results_type::endpoint_type &);

  void onWrite(beast::error_code ec, std::size_t bytes_transferred);

  void onRead(beast::error_code ec, std::size_t bytes_transferred);

private:
  tcp::resolver resolver_;
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  http::response<http::string_body> res_;
  std::shared_ptr<std::string> body_save;
  http::request<http::string_body> req_;
};

class HTTPClient {
public:
  http::response<http::string_body> _sendRequest(const http::request<http::string_body>& request,
                                                 const std::string& host,
                                                 const std::string& port);

private:
  net::io_context context_;
  std::shared_ptr<Session> s;
};

class RequestSender {
public:
  RequestSender(std::string host, std::string port) : host_(std::move(host)), port_(std::move(port)) {}
  http::response<http::string_body> sendRequest(const http::request<http::string_body> &request) const;

public:
  std::string host_;
  std::string port_;
};

http::request<http::string_body> constructRequest(http::verb method, const std::string &target, std::string body);
}
#endif
