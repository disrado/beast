#pragma once

#include "https/Types.hpp"


namespace https
{


class BaseRequestHandler
{
public:
	virtual ~BaseRequestHandler();

	virtual ResponseShPtr Handle(Request&& request) = 0;
};


}	// namespace https