#pragma once
#include "CTriangle.h"
#include "pch.h"

CTriangle::CTriangle(const std::vector<std::string>& args)
{
	if (args.size() < 9)
	{
		throw std::invalid_argument("Triangle must contain 8 arguments in format: 'triangle %vertex1_x% %vertex1_y% %vertex2_x% %vertex2_y% %vertex3_x% %vertex3_y% %outline_color% %fill_color%'");
	}
	m_vertex1.FromString(args[1] + " " + args[2]);
	m_vertex2.FromString(args[3] + " " + args[4]);
	m_vertex3.FromString(args[5] + " " + args[6]);
	SetOutlineColorByString(args[7]);
	SetFillColorByString(args[8]);
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

std::string CTriangle::ToString() const
{
	return "triangle " + m_vertex1.ToString() + " " + m_vertex2.ToString() + " " + m_vertex3.ToString() + " " + std::to_string(m_outlineColor) + " " + std::to_string(m_fillColor);
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
