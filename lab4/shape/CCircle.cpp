#pragma once
#include "pch.h"
#include "CCircle.h"

CCircle::CCircle(const CPoint& center, double radius, uint32_t fillColor, uint32_t outlineColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape(fillColor, outlineColor)
{
	if (m_radius < 0)
	{
		throw std::invalid_argument("Radius must be positive");
	}
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

std::string CCircle::GetShapeInfo() const
{
	return "circle "
		+ m_center.ToString() + ' '
		+ std::to_string(m_radius);
}
