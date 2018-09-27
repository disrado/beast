#pragma once

#include <boost/exception/all.hpp>

#include <string_view>
#include <iostream>


template<typename exceptionType>
void ThrowError(const std::string& message)
{
	BOOST_THROW_EXCEPTION(exceptionType(message));
}


template<typename exceptionType>
void LogAndThrow(const std::string& message)
{
	//TODO: Need to add logger!
	std::cout << message << std::endl;
	ThrowError<exceptionType>(message);
}