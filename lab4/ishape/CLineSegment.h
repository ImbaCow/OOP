#pragma once
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const std::vector<std::string>& args);
	virtual ~CLineSegment(){};

	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;

	void SetStartPointByString(const std::string& string);
	void SetEndPointByString(const std::string& string);
};
