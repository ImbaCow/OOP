#pragma once
#include "pch.h"
#include "ShapeArray.h"

std::vector<std::unique_ptr<IShape>> GetShapeArrayFromStream(std::istream& input)
{
	std::vector<std::unique_ptr<IShape>> shapeArr;
	std::string shapeInfo;

	for (size_t lineNumber = 1; std::getline(input, shapeInfo); ++lineNumber)
	{
		try
		{
			shapeArr.push_back(ShapeFactory::CreateShape(shapeInfo));
		}
		catch (const std::exception& e)
		{
			throw std::invalid_argument("Error on line " + std::to_string(lineNumber) + ". " + e.what());
		}
	}

	return shapeArr;
}

std::string ShapeArrayToString(const std::vector<std::unique_ptr<IShape>>& shapeArr)
{
	std::string result;
	for (const auto& shape : shapeArr)
	{
		result += shape->ToString() + '\n';
	}
	return result;
}

MaxMinShapes GetMaxAreaMinPerimeterShapes(const std::vector<std::unique_ptr<IShape>>& shapeArr)
{
	ShapeMathResult maxAreaShape;
	ShapeMathResult minPerimeterShape;

	for (const auto& shape : shapeArr)
	{
		if (maxAreaShape.info.empty() || maxAreaShape.area < shape->GetArea())
		{
			maxAreaShape = { shape->ToString(), shape->GetArea(), shape->GetPerimeter() };
		}
		if (minPerimeterShape.info.empty() || minPerimeterShape.perimeter > shape->GetPerimeter())
		{
			minPerimeterShape = { shape->ToString(), shape->GetArea(), shape->GetPerimeter() };
		}
	}
	return { maxAreaShape, minPerimeterShape };
}

MaxMinShapes FindMaxAreMinPerimeterShapesFromStream(std::istream& input)
{
	auto shapeArr = GetShapeArrayFromStream(input);
	auto minMax = GetMaxAreaMinPerimeterShapes(shapeArr);
	return minMax;
}
