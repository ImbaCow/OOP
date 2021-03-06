#pragma once
#include "pch.h"
#include "ShapeArray.h"
#include "ShapeFactory.h"

std::optional<std::ifstream> AskForInput()
{
	std::string inputName;
	std::cout << "Type input file name: ";
	std::cin >> inputName;

	std::ifstream input(inputName);
	if (!input.is_open())
	{
		std::cerr << "Input file not found." << std::endl;
		return std::nullopt;
	}
	return input;
}

std::optional<std::vector<std::unique_ptr<IShape>>> GetShapes(std::ifstream& input)
{
	try
	{
		return GetShapeArrayFromStream(input);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return std::nullopt;
	}
}

void WriteSearchResultShapes(const MaxMinShapes& shapes)
{

	if (!shapes.maxAreaShape.info.empty())
	{
		std::cout << "Max area shape: " << shapes.maxAreaShape.ToString() << std::endl;
	}
	if (!shapes.minPerimeterShape.info.empty())
	{
		std::cout << "Min perimeter shape: " << shapes.minPerimeterShape.ToString() << std::endl;
	}
}

int main()
{
	auto inputOpt = AskForInput();
	if (!inputOpt)
	{
		return 1;
	}

	auto shapeArrOpt = GetShapes(inputOpt.value());
	if (!shapeArrOpt)
	{
		return 1;
	}

	std::cout << "Input shapes: " << std::endl
			  << ShapeArrayToString(shapeArrOpt.value()) << std::endl
			  << std::endl;

	MaxMinShapes searchResult = GetMaxAreaMinPerimeterShapes(shapeArrOpt.value());
	WriteSearchResultShapes(searchResult);
}
