#pragma once

#include "https/handlers/BaseRequestHandler.hpp"
#include "https/Types.hpp"


namespace https
{


class Unknown : public BaseRequestHandler
{
public:
	virtual ResponseShPtr Handle(Request&& request) override;
};


}	// namespace https