#pragma once
#include "CPoint.h"

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const;

	virtual ~IShape(){};

protected:
	uint32_t m_outlineColor;

	static uint32_t HexStringToUint(const std::string& string);
	void SetOutlineColorByString(const std::string& string);
};
