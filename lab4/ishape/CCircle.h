#pragma once
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(const std::vector<std::string>& args);
	virtual ~CCircle(){};

	double GetArea() const;
	double GetPerimeter() const;

	std::string ToString() const;

	CPoint GetCenter() const;
	void SetCenterByString(const std::string& string);

	double GetRadius() const;
	void SetRadiusByString(const std::string& string);

private:
	CPoint m_center;
	double m_radius;
};
