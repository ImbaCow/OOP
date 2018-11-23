#pragma once
#include "ISolidShape.h"
class CCircle :
	private ISolidShape
{
public:
	CCircle(const std::string * inputInfo);
	virtual ~CCircle() {};

	double GetArea() const;
	double GetPerimeter() const;

	std::string ToString() const;

	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;

	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint m_center;
	double m_radius;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

