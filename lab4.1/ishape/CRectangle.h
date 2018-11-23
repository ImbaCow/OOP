#pragma once
#include "ISolidShape.h"
class CRectangle :
	private ISolidShape
{
public:
	CRectangle(const std::string * inputInfo);
	virtual ~CRectangle() {};

	double GetArea() const;
	double GetPerimeter() const;

	std::string ToString() const;

	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	double GetWidth() const;
	double GetHeight() const;
private:
	CPoint m_leftTop;

	double m_width;
	double m_height;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

