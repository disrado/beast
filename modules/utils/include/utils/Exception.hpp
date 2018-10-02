#pragma once

#include <logger/Logger.hpp>

#include <boost/exception/all.hpp>

#include <string_view>
#include <iostream>


namespace utils
{


template<typename exceptionType>
void Throw(const std::string& message)
{
	BOOST_THROW_EXCEPTION(exceptionType(message));
}


}	// namespace utils
