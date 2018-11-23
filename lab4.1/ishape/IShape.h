#pragma once
#include "CPoint.h"

enum Shape
{
	Line,
	Rectangle,
	Triangle,
	Circle
};

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

	virtual ~IShape() {};

	static std::unique_ptr<IShape> GetShape(const std::string & shapeName);
	static Shape ShapeStringToEnum(const std::string & shapeName);
};
