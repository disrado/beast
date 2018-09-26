#include "https/handlers/Root.hpp"

#include <boost/beast/http.hpp>

#include <memory>


namespace https
{


ResponseShPtr Root::Handle(Request&& request)
{
	auto res{ std::make_shared<Response>(http::status::ok, request.version()) };
	res->set(http::field::server, "Beast");
	res->body() = "Ok";
	res->prepare_payload();

	return res;
}


}	// namespace https