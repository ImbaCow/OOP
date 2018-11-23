#pragma once
#include "IShape.h"
class ISolidShape :
	virtual IShape
{
	virtual uint32_t GetFillColor() const = 0;
};
