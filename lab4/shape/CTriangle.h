#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, uint32_t fillColor, uint32_t outlineColor);
	virtual ~CTriangle(){};

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

protected:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;

	std::string GetShapeInfo() const override;
};
