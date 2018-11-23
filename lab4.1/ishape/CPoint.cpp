#include "CPoint.h"

double CPoint::GetNorm() const
{
	return std::hypot(x, y);
}

std::string CPoint::ToString() const
{
	return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
}

CPoint CPoint::operator+(const CPoint & b) const
{
	return { this->x + b.x, this->y + b.y };
}

CPoint CPoint::operator-(const CPoint & b) const
{
	return { this->x - b.x, this->y - b.y };
}
