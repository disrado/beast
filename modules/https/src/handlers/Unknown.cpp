#include "https/handlers/Unknown.hpp"

#include <boost/beast/http.hpp>

#include <memory>


namespace {
	namespace http = boost::beast::http;
}


namespace https
{


ResponseShPtr Unknown::Handle(Request&& request)
{
	auto res{ std::make_shared<Response>(http::status::bad_request, request.version()) };
	res->set(http::field::server, "Beast");
	res->body() = "Unknown route";
	res->prepare_payload();

	return res;
}


}	// namespace https