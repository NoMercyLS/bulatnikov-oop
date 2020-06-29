#pragma once
#include "source.h"
#include "const.h"
class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string& message);
};

