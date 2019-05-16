#include "pch.h"
#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& message)
	: invalid_argument(message)
{
}
CUrlParsingError::CUrlParsingError(const char* message)
	: invalid_argument(message)
{
}