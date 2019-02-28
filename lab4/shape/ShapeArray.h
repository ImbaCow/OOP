#pragma once
#include "ShapeFactory.h"

struct ShapeMathResult
{
	std::string info;
	double area;
	double perimeter;

	std::string ToString() const
	{
		return info 
			+ "; area: " + std::to_string(area)
			+ "; perimeter: " + std::to_string(perimeter);
	}
};

struct MaxMinShapes
{
	ShapeMathResult maxAreaShape;
	ShapeMathResult minPerimeterShape;
};

std::vector<std::unique_ptr<IShape>> GetShapeArrayFromStream(std::istream& input);

std::string ShapeArrayToString(const std::vector<std::unique_ptr<IShape>>& shapeArr);

MaxMinShapes GetMaxAreaMinPerimeterShapes(const std::vector<std::unique_ptr<IShape>>& shapeArr);

MaxMinShapes FindMaxAreMinPerimeterShapesFromStream(std::istream& input);
