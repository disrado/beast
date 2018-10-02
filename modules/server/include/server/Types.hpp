#pragma once

#include <nlohmann/json.hpp>

#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <memory>


namespace bs
{


namespace http = boost::beast::http;
namespace nl = nlohmann;

template<typename Body = http::string_body, typename Fields = http::fields>
using Response = http::message<false, Body, Fields>;

template<typename Body = http::string_body, typename Fields = http::fields>
using Request = http::message<true, Body, Fields>;

template<typename Body = http::string_body, typename Fields = http::fields>
using ResponseShPtr = std::shared_ptr<Response<Body, Fields>>;

template<typename Body = http::string_body, typename Fields = http::fields>
using RequestShPtr = std::shared_ptr<Request<Body, Fields>>;

using tcp = boost::asio::ip::tcp;
using Host = boost::asio::ip::address;
using Port = uint16_t;


}	// namespace bs