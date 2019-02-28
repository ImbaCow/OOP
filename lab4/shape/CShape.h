#pragma once
#include "IShape.h"

class CShape : virtual public IShape
{
public:
	CShape(uint32_t outlineColor);
	virtual ~CShape(){};

	uint32_t GetOutlineColor() const final;
	std::string ToString() const override;

protected:
	uint32_t m_outlineColor;
		
	virtual std::string GetShapeInfo() const = 0;
};
