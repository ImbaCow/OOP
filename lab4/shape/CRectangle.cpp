#pragma once
#include "pch.h"
#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, double height, double width, uint32_t fillColor, uint32_t outlineColor)
	: m_leftTop(leftTop)
	, m_height(height)
	, m_width(width)
	, CSolidShape(fillColor, outlineColor)
{
	if (m_height < 0 || m_width < 0)
	{
		throw std::invalid_argument("Height and width must be positive values");
	}
}

double CRectangle::GetArea() const
{
	return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_height + m_width);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return { m_leftTop.x + m_width, m_leftTop.y - m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

std::string CRectangle::GetShapeInfo() const
{
	return "rectangle "
		+ m_leftTop.ToString() + ' '
		+ std::to_string(m_width) + ' '
		+ std::to_string(m_height);
}
