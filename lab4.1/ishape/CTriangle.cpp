#include "pch.h"
#include "CTriangle.h"


CTriangle::CTriangle(const std::string * inputInfo)
{
}

double CTriangle::GetArea() const
{
	double side1 = (m_vertex1 - m_vertex2).GetNorm();
	double side2 = (m_vertex2 - m_vertex3).GetNorm();
	double side3 = (m_vertex3 - m_vertex1).GetNorm();
	double p = side1 + side2 + side3;
	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

double CTriangle::GetPerimeter() const
{
	double side1 = (m_vertex1 - m_vertex2).GetNorm();
	double side2 = (m_vertex2 - m_vertex3).GetNorm();
	double side3 = (m_vertex3 - m_vertex1).GetNorm();
	return side1 + side2 + side3;
}

std::string CTriangle::ToString() const
{
	return "triangle " + m_vertex1.ToString() + 
		" " + m_vertex2.ToString() + 
		" " + m_vertex3.ToString() + 
		" " + std::to_string(m_outlineColor) + 
		" " + std::to_string(m_fillColor);
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
