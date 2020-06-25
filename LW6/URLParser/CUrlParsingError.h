#pragma once
#include "source.h"
class CUrlParsingError : public invalid_argument
{
public:
	CUrlParsingError(const string& message);
};

