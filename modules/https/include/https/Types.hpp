#pragma once

#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace https {
	namespace http = boost::beast::http;
}

namespace https
{

using Response = http::message<false, http::string_body, http::fields>;
using Request = http::message<true, http::string_body, http::fields>;
using tcp = boost::asio::ip::tcp;
using Address = boost::asio::ip::address;
using Port = uint16_t;

}	// namespace https