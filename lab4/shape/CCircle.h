#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint& center, double radius, uint32_t fillColor, uint32_t outlineColor);
	virtual ~CCircle(){};

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

protected:
	CPoint m_center;
	double m_radius;

	std::string GetShapeInfo() const override;
};
