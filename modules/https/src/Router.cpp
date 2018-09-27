#include "https/Router.hpp"
#include "https/handlers/All.hpp"

#include <logger/Logger.hpp>

#include <fmt/format.h>

#include <boost/beast/core.hpp>


namespace https
{


Router& Router::Instance()
{
	static Router instance;
	return instance;
}


std::unique_ptr<BaseRequestHandler> Router::GerHandler(std::string_view route)
{
	logger::SLOG(logger::Severity::info, "Routing")
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


}	// namespace https