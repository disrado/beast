#pragma once

#include "https/handlers/BaseRequestHandler.hpp"


namespace https
{


class Another : public BaseRequestHandler
{
public:
	virtual ResponseShPtr Handle(Request&& request) override;
};


}	// namespace https