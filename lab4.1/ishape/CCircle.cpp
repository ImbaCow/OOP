#define _USE_MATH_DEFINES
#include "pch.h"
#include "CCircle.h"


CCircle::CCircle(const std::string * inputInfo)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	return "circle " + m_center.ToString() + 
		" " + std::to_string(m_radius) +
		" " + std::to_string(m_outlineColor) + 
		" " + std::to_string(m_fillColor);
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
