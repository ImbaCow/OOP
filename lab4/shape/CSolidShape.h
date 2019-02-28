#pragma once
#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape : public CShape
	, public ISolidShape
{
public:
	CSolidShape(uint32_t fillColor, uint32_t outlineColor);
	virtual ~CSolidShape(){};

	uint32_t GetFillColor() const final;
	std::string ToString() const override;

protected:
	uint32_t m_fillColor;
};
