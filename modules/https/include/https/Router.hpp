#pragma once

#include "https/Types.hpp"
#include "https/handlers/BaseRequestHandler.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <string_view>
#include <unordered_map>


namespace https
{


class Router
{
public:
	static Router& Instance();

	std::unique_ptr<BaseRequestHandler> GerHandler(std::string_view route);
};


}	// namespace https