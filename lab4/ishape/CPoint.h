#pragma once

struct CPoint
{
	double x;
	double y;

	CPoint() = default;

	double GetNorm() const;
	std::string ToString() const;
	void FromString(const std::string& string);

	CPoint operator+(const CPoint& b) const;
	CPoint operator-(const CPoint& b) const;
};
