#pragma once

#include <nlohmann/json.hpp>

#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <memory>


namespace https
{


namespace http = boost::beast::http;
namespace nl = nlohmann;

using Response = http::message<false, http::string_body, http::fields>;
using ResponseShPtr = std::shared_ptr<Response>;
using Request = http::message<true, http::string_body, http::fields>;
using RequestShPtr = std::shared_ptr<Request>;
using tcp = boost::asio::ip::tcp;
using Host = boost::asio::ip::address;
using Port = uint16_t;


}	// namespace https