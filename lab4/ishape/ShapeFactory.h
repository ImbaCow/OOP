#pragma once
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "boost/algorithm/string.hpp"

enum Shape
{
	Circle,
	Line,
	Rectangle,
	Triangle
};

class ShapeFactory
{
public:
	static IShape* GetShape(const std::string& shapeName);

private:
	static std::vector<std::string> GetArgsFromString(const std::string& command);
	static Shape GetEnumFromString(std::string shapeName);
};
