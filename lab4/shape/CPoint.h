#pragma once

struct CPoint
{
	double x;
	double y;

	double GetNorm() const;
	std::string ToString() const;

	CPoint operator+(const CPoint& b) const;
	CPoint operator-(const CPoint& b) const;
};
