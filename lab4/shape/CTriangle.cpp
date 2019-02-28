#pragma once
#include "pch.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, uint32_t fillColor, uint32_t outlineColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CSolidShape(fillColor, outlineColor)
{
}

double CTriangle::GetArea() const
{
	double side1 = (m_vertex1 - m_vertex2).GetNorm();
	double side2 = (m_vertex2 - m_vertex3).GetNorm();
	double side3 = (m_vertex3 - m_vertex1).GetNorm();
	double p = (side1 + side2 + side3) / 2;
	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

double CTriangle::GetPerimeter() const
{
	double side1 = (m_vertex1 - m_vertex2).GetNorm();
	double side2 = (m_vertex2 - m_vertex3).GetNorm();
	double side3 = (m_vertex3 - m_vertex1).GetNorm();
	return side1 + side2 + side3;
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

std::string CTriangle::GetShapeInfo() const
{
	return "triangle "
		+ m_vertex1.ToString() + ' '
		+ m_vertex2.ToString() + ' '
		+ m_vertex3.ToString();
}
