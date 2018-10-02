#include "server/Router.hpp"
#include "server/handlers/All.hpp"

#include <logger/Logger.hpp>

#include <fmt/format.h>

#include <boost/beast/core.hpp>


namespace bs
{


Router& Router::Instance()
{
	static Router instance;
	return instance;
}


std::unique_ptr<BaseRequestHandler> Router::GerHandler(std::string_view route)
{
	lg::SLOG(lg::Severity::info, "Routing")
		<< fmt::format("Processed route: \"{}\"", route); 

	lg::SLOGGF(lg::Severity::info, "Routing")
		<< fmt::format("Processed route: \"{}\"", route); 

	if (route == "/")
	{
		return std::make_unique<Root>();
	}
	else if (route == "/another")
	{
		return std::make_unique<Another>();
	}

	return std::make_unique<Unknown>();
}


}	// namespace bs