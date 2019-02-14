#pragma once
#include "CRectangle.h"
#include "pch.h"

CRectangle::CRectangle(const std::vector<std::string>& args)
{
	if (args.size() < 7)
	{
		throw std::invalid_argument("Rectangle must contain 6 arguments in format: 'rectangle %left_top_x% %left_top_y% %width% %height% %outline_color% %fill_color%'");
	}

	m_leftTop.FromString(args[1] + " " + args[2]);
	SetWidthByString(args[3]);
	SetHeightByString(args[4]);
	SetOutlineColorByString(args[5]);
	SetFillColorByString(args[6]);
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
	return "rectangle " + m_leftTop.ToString() + " " + std::to_string(m_width) + " " + std::to_string(m_height) + " " + std::to_string(m_outlineColor) + " " + std::to_string(m_fillColor);
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

void CRectangle::SetWidthByString(const std::string& string)
{
	std::stringstream ss(string);
	double value;
	if (!(ss >> value) || value < 0)
	{
		throw std::invalid_argument("Invalid width, shoud be positive float number");
	}
	m_width = value;
}

void CRectangle::SetHeightByString(const std::string& string)
{
	std::stringstream ss(string);
	double value;
	if (!(ss >> value) || value < 0)
	{
		throw std::invalid_argument("Invalid height, shoud be positive float number");
	}
	m_height = value;
}
