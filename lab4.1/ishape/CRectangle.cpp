#include "pch.h"
#include "CRectangle.h"


CRectangle::CRectangle(const std::string * inputInfo)
{
}

double CRectangle::GetArea() const
{
	return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_height + m_width);
}

std::string CRectangle::ToString() const
{
	return "rectangle " + m_leftTop.ToString() + 
		" " + std::to_string(m_width) + 
		" " + std::to_string(m_height) + 
		" " + std::to_string(m_outlineColor) + 
		" " + std::to_string(m_fillColor);
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return {m_leftTop.x + m_width, m_leftTop.y - m_height};
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
