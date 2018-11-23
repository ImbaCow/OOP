#include "pch.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"

#include "IShape.h"

std::unique_ptr<IShape> IShape::GetShape(const std::string & shapeName)
{
	Shape shape = ShapeStringToEnum(shapeName);
	IShape * shapePtr;
	switch (shape)
	{
	case Line:
		shapePtr = std::unique_ptr<CLineSegment>;
	case Rectangle:
	case Triangle:
	case Circle:
	default:
		throw std::logic_error("Unhandled shape");
	}
}

Shape IShape::ShapeStringToEnum(const std::string & shapeName)
{
	if (shapeName == "line")
	{
		return Line;
	}
	if (shapeName == "rectangle")
	{
		return Rectangle;
	}
	if (shapeName == "triangle")
	{
		return Triangle;
	}
	if (shapeName == "circle")
	{
		return Circle;
	}
	throw std::invalid_argument("Undefined shape: " + shapeName);
}
