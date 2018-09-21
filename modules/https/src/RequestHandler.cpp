#include "https/RequestHandler.hpp"

#include <boost/beast/http.hpp>

namespace {
	namespace http = boost::beast::http;
}

namespace https
{

Response RequestHandler::HandleRquest(Request&& req)
{
	Response res{ http::status::ok, req.version() };
	res.set(http::field::server, "Beast");
	res.body() = "Ok";
	res.prepare_payload();

	return res;
}

}	// namespace https