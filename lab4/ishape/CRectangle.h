#pragma once
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const std::vector<std::string>& args);
	virtual ~CRectangle(){};

	double GetArea() const;
	double GetPerimeter() const;

	std::string ToString() const;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;

	double m_width;
	double m_height;

	void SetWidthByString(const std::string& string);
	void SetHeightByString(const std::string& string);
};
