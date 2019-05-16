#pragma once

class CUrlParsingError
	: public std::invalid_argument
{
public:
	explicit CUrlParsingError(const std::string& message);
	explicit CUrlParsingError(const char* message);
};
