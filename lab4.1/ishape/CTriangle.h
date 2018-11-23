#pragma once
#include "ISolidShape.h"
class CTriangle :
	private ISolidShape
{
public:
	CTriangle(const std::string * inputInfo);
	virtual ~CTriangle() {};

	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;
	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;

	uint32_t m_outlineColor = 0;
	uint32_t m_fillColor = 0;
};

