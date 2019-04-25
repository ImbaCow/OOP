#include "pch.h"
#include "BaseFnValue.h"

void BaseFnValue::Set(double value)
{
	throw std::logic_error("Cannot set " + std::to_string(value) + " to function");
}
