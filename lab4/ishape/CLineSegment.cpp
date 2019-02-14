#pragma once
#include "CLineSegment.h"
#include "pch.h"

CLineSegment::CLineSegment(const std::vector<std::string>& args)
{
	if (args.size() < 6)
	{
		throw std::invalid_argument("Line must contain 5 arguments in format: 'line %start_x% %start_y% %end_x% %end_y% %outline_color%'");
	}
	SetStartPointByString(args[1] + " " + args[2]);
	SetEndPointByString(args[3] + " " + args[4]);
	SetOutlineColorByString(args[5]);
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return 2 * (m_startPoint - m_endPoint).GetNorm();
}

std::string CLineSegment::ToString() const
{
	return "line " + m_startPoint.ToString() + " " + m_endPoint.ToString() + " " + std::to_string(m_outlineColor);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::SetStartPointByString(const std::string& string)
{
	try
	{
		m_startPoint.FromString(string);
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Invalid start point");
	}
}

void CLineSegment::SetEndPointByString(const std::string& string)
{
	try
	{
		m_endPoint.FromString(string);
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Invalid end point");
	}
}
