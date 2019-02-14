#pragma once
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const std::vector<std::string>& args);
	virtual ~CTriangle(){};

	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};
