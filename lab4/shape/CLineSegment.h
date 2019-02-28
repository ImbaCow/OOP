#pragma once
#include "CPoint.h"
#include "CShape.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor);
	virtual ~CLineSegment(){};

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;

	std::string GetShapeInfo() const override;
};
