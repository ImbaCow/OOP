#pragma once
#include "CCircle.h"
#include "pch.h"

CCircle::CCircle(const std::vector<std::string>& args)
{
	if (args.size() < 6)
	{
		throw std::invalid_argument("Circle must contain 5 arguments in format: 'circle %center_x% %center_y% %radius% %outline_color% %fill_color%'");
	}
	SetCenterByString(args[1] + " " + args[2]);
	SetRadiusByString(args[3]);
	SetOutlineColorByString(args[4]);
	SetFillColorByString(args[5]);
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
	return "circle " + m_center.ToString() + " " + std::to_string(m_radius) + " " + std::to_string(m_outlineColor) + " " + std::to_string(m_fillColor);
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

void CCircle::SetCenterByString(const std::string& string)
{
	try
	{
		m_center.FromString(string);
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Invalid center point");
	}
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::SetRadiusByString(const std::string& string)
{
	std::stringstream ss(string);
	double value;
	if (!(ss >> value) || value < 0)
	{
		throw std::invalid_argument("Invalid radius");
	}
	m_radius = value;
}
