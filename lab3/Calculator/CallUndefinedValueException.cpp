#include "pch.h"
#include "CallUndefinedValueException.h"

CallUndefinedValueException::CallUndefinedValueException(const std::string& message)
	: logic_error(message.c_str())
{
}

CallUndefinedValueException::CallUndefinedValueException(const char* message)
	: logic_error(message)
{
}
