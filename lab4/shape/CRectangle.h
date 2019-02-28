#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint& leftTop, double height, double width, uint32_t fillColor, uint32_t outlineColor);
	virtual ~CRectangle(){};

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	double GetWidth() const;
	double GetHeight() const;

protected:
	CPoint m_leftTop;

	double m_width;
	double m_height;

	std::string GetShapeInfo() const override;
};
