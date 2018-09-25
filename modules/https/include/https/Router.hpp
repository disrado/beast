#pragma once

#include "https/Types.hpp"
#include "https/handlers/BaseRequestHandler.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>


namespace https
{


class Router
{
public:
	using RouteMap = std::unordered_map<
		std::string, 
		std::function<std::shared_ptr<BaseRequestHandler>()>
	>;

private:
	Router();

public:
	static Router& Instance();

	std::shared_ptr<BaseRequestHandler> GerHandler(std::string route);

private:
	mutable std::mutex m_mapMtx;
	RouteMap m_routes;
};


}	// namespace https