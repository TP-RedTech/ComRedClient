//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP client, asynchronous
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
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

void
fail(beast::error_code ec, char const *what) {
  std::cerr << what << ": " << ec.message() << "\n";
}

class session : public std::enable_shared_from_this<session> {
  tcp::resolver resolver_;
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  http::request<http::empty_body> req_;
  http::response<http::string_body> res_;

public:
  explicit
  session(net::io_context &ioc)
      : resolver_(net::make_strand(ioc)), stream_(net::make_strand(ioc)) {
  }

  void run(
      char const *host,
      char const *port,
      char const *target,
      int version) {
    req_.version(version);
    req_.method(http::verb::get);
    req_.target(target);
    req_.set(http::field::host, host);
    req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    resolver_.async_resolve(
        host,
        port,
        beast::bind_front_handler(
            &session::on_resolve,
            shared_from_this()));
  }

  void
  on_resolve(
      beast::error_code ec,
      tcp::resolver::results_type results) {
    if (ec)
      return fail(ec, "resolve");

    stream_.expires_after(std::chrono::seconds(30));

    stream_.async_connect(
        results,
        beast::bind_front_handler(
            &session::on_connect,
            shared_from_this()));
  }

  void
  on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type) {
    if (ec)
      return fail(ec, "connect");

    stream_.expires_after(std::chrono::seconds(30));

    http::async_write(stream_, req_,
                      beast::bind_front_handler(
                          &session::on_write,
                          shared_from_this()));
  }

  void on_write(
      beast::error_code ec,
      std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
      return fail(ec, "write");

    // Receive the HTTP response
    http::async_read(stream_, buffer_, res_,
                     beast::bind_front_handler(
                         &session::on_read,
                         shared_from_this()));
  }

  void on_read(
      beast::error_code ec,
      std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
      return fail(ec, "read");

    std::cout << res_ << std::endl;

    stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected)
      return fail(ec, "shutdown");
  }
};

class Client {
public:
  void run() {
    auto const host = "127.0.0.1";
    auto const port = "5555";
    auto const target = "/connect";
    int version = 11;

    net::io_context ioc;
    std::make_shared<session>(ioc)->run(host, port, target, version);
    ioc.run();
  }
};

int main(int argc, char **argv) {
}