#pragma once
#include "pch.h"
#include "ShapeFactory.h"

std::unique_ptr<IShape> ShapeFactory::CreateShape(const std::string& shapeInfo)
{
	std::vector<std::string> args = GetArgsFromString(shapeInfo);
	std::string shapeName = args[0];

	if (shapeName == "line")
	{
		return CreateLine(args);
	}
	else if (shapeName == "rectangle")
	{
		return CreateRectangle(args);
	}
	else if (shapeName == "triangle")
	{
		return CreateTriangle(args);
	}
	else if (shapeName == "circle")
	{
		return CreateCircle(args);
	}
	else
	{
		throw std::invalid_argument("Unhandled shape: " + shapeName);
	}
}

std::vector<std::string> ShapeFactory::GetArgsFromString(std::string argsString)
{
	std::vector<std::string> args;
	boost::trim_all(argsString);
	boost::split(args, argsString, [](char ch) {
		return ch == ' ';
	});
	return args;
}

CPoint ShapeFactory::MakePoint(const std::string& x, const std::string& y)
{
	try
	{
		return {
			MakeDouble(x),
			MakeDouble(y)
		};
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Uncorrect point values");
	}
}

double ShapeFactory::MakeDouble(const std::string& numberString)
{
	try
	{
		return boost::lexical_cast<double>(numberString);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Uncorrect float number");
	}
}

uint32_t ShapeFactory::MakeUintFromHex(const std::string& hex)
{
	std::stringstream ss;
	ss << std::hex << hex;
	uint32_t result;
	if (!(ss >> result))
	{
		throw std::invalid_argument("Uncorrect hex color");
	}
	return result;
}

std::unique_ptr<CLineSegment> ShapeFactory::CreateLine(const std::vector<std::string>& args)
{
	if (args.size() < 6)
	{
		throw std::invalid_argument("Line must contain 5 arguments in format: 'line %start_x% %start_y% %end_x% %end_y% %outline_color%'");
	}
	CPoint startPoint = MakePoint(args[1], args[2]);
	CPoint endPoint = MakePoint(args[3], args[4]);
	uint32_t outlineColor = MakeUintFromHex(args[5]);

	return std::make_unique<CLineSegment>(startPoint, endPoint, outlineColor);
}

std::unique_ptr<CRectangle> ShapeFactory::CreateRectangle(const std::vector<std::string>& args)
{
	if (args.size() < 7)
	{
		throw std::invalid_argument("Rectangle must contain 6 arguments in format: 'rectangle %left_top_x% %left_top_y% %height% %width% %fill_color% %outline_color%'");
	}

	CPoint leftTop = MakePoint(args[1], args[2]);
	double height = MakeDouble(args[3]);
	double width = MakeDouble(args[4]);
	uint32_t fillColor = MakeUintFromHex(args[5]);
	uint32_t outlineColor = MakeUintFromHex(args[6]);

	return std::make_unique<CRectangle>(leftTop, width, height, fillColor, outlineColor);
}

std::unique_ptr<CTriangle> ShapeFactory::CreateTriangle(const std::vector<std::string>& args)
{
	if (args.size() < 9)
	{
		throw std::invalid_argument("Triangle must contain 8 arguments in format: 'triangle %vertex1_x% %vertex1_y% %vertex2_x% %vertex2_y% %vertex3_x% %vertex3_y% %fill_color% %outline_color%'");
	}
	CPoint vertex1 = MakePoint(args[1], args[2]);
	CPoint vertex2 = MakePoint(args[3], args[4]);
	CPoint vertex3 = MakePoint(args[5], args[6]);
	uint32_t fillColor = MakeUintFromHex(args[7]);
	uint32_t outlineColor = MakeUintFromHex(args[8]);

	return std::make_unique<CTriangle>(vertex1, vertex2, vertex3, fillColor, outlineColor);
}

std::unique_ptr<CCircle> ShapeFactory::CreateCircle(const std::vector<std::string>& args)
{
	if (args.size() < 6)
	{
		throw std::invalid_argument("circle must contain 5 arguments in format: 'circle %center_x% %center_y% %radius% %fill_color% %outline_color%'");
	}
	CPoint center = MakePoint(args[1], args[2]);
	double radius = MakeDouble(args[3]);
	uint32_t fillColor = MakeUintFromHex(args[4]);
	uint32_t outlineColor = MakeUintFromHex(args[5]);

	return std::make_unique<CCircle>(center, radius, fillColor, outlineColor);
}
