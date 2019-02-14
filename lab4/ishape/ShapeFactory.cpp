#pragma once
#include "ShapeFactory.h"
#include "pch.h"

IShape* ShapeFactory::GetShape(const std::string& shapeInfo)
{
	std::vector<std::string> args = GetArgsFromString(shapeInfo);
	std::string shapeName = args[0];
	Shape shape = GetEnumFromString(shapeName);
	IShape* shapeObj;

	switch (shape)
	{
	case Circle:
		shapeObj = new CCircle(args);
		break;
	case Line:
		shapeObj = new CLineSegment(args);
		break;
	case Rectangle:
		shapeObj = new CRectangle(args);
		break;
	case Triangle:
		shapeObj = new CTriangle(args);
		break;
	default:
		throw std::invalid_argument("Unhandled shape: " + shapeName);
	}

	return shapeObj;
}

std::vector<std::string> ShapeFactory::GetArgsFromString(const std::string& argsString)
{
	std::vector<std::string> args;
	boost::split(args, argsString, [](char ch) {
		return ch == ' ';
	});
	return args;
}

Shape ShapeFactory::GetEnumFromString(std::string shapeName)
{
	Shape shape;
	if (shapeName == "line")
	{
		shape = Line;
	}
	else if (shapeName == "rectangle")
	{
		shape = Rectangle;
	}
	else if (shapeName == "triangle")
	{
		shape = Triangle;
	}
	else if (shapeName == "circle")
	{
		shape = Circle;
	}
	else
	{
		throw std::invalid_argument("Unhandled shape: " + shapeName);
	}
	return shape;
}
