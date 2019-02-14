#pragma once
#include "IShape.h"

class ISolidShape : virtual public IShape
{
public:
	virtual uint32_t GetFillColor() const;

	virtual ~ISolidShape(){};

protected:
	uint32_t m_fillColor;

	virtual void SetFillColorByString(const std::string& string);
};
