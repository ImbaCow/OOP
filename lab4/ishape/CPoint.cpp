#pragma once
#include "CPoint.h"
#include "pch.h"

double CPoint::GetNorm() const
{
	return std::hypot(x, y);
}

std::string CPoint::ToString() const
{
	return std::to_string(x) + " " + std::to_string(y);
}

void CPoint::FromString(const std::string& string)
{
	std::stringstream sstream(string);
	if (!(sstream >> x) || !(sstream >> y))
	{
		throw std::invalid_argument("Invalid point string");
	}
}

CPoint CPoint::operator+(const CPoint& b) const
{
	return { this->x + b.x, this->y + b.y };
}

CPoint CPoint::operator-(const CPoint& b) const
{
	return { this->x - b.x, this->y - b.y };
}
