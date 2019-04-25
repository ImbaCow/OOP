#pragma once

class CallUndefinedValueException
	: public std::logic_error
{
public:
	explicit CallUndefinedValueException(const std::string& message);
	explicit CallUndefinedValueException(const char* message);
};
