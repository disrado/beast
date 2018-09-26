#include "https/handlers/Another.hpp"

#include <boost/beast/http.hpp>

#include <memory>


namespace https
{


ResponseShPtr Another::Handle(Request&& request)
{
	auto res{ std::make_shared<Response>(http::status::ok, request.version()) };
	res->set(http::field::server, "Beast");
	res->body() = "Another response";
	res->prepare_payload();

	return res;
}


}	// namespace https