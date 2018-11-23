#include "pch.h"
#include "CLineSegment.h"

CLineSegment::CLineSegment(const std::string * inputInfo)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return (m_startPoint - m_endPoint).GetNorm();
}

std::string CLineSegment::ToString() const
{
	return "line " + m_startPoint.ToString() + 
		" " + m_endPoint.ToString() + 
		" " + std::to_string(m_outlineColor);
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
