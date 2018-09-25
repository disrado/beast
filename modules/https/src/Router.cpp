#include "https/Router.hpp"
#include "https/handlers/All.hpp"

#include <boost/beast/core.hpp>


namespace https
{


Router::Router()
{
	m_routes = {
		{ "/", [] { return std::make_shared<Root>(); } },
		{ "/doodoo", [] { return std::make_shared<Root>(); } }
	}; 
}


Router& Router::Instance()
{
	static Router instance;
	return instance;
}


//TODO: replace parameter type by string_view(need to update complier)
std::shared_ptr<BaseRequestHandler> Router::GerHandler(std::string route)
{
	try {
		{ std::lock_guard<std::mutex> lGuard(m_mapMtx);
			return m_routes.at(route)();
		}
	} catch (const std::out_of_range& exception) {
		return std::make_shared<Unknown>();
	}
	
}


}	// namespace https