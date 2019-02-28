#pragma once
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "pch.h"

class ShapeFactory
{
public:
	static std::unique_ptr<IShape> CreateShape(const std::string& shapeInfo);

private:
	static std::vector<std::string> GetArgsFromString(std::string argsString);

	static CPoint MakePoint(const std::string& x, const std::string& y);
	static double MakeDouble(const std::string& numberString);
	static uint32_t MakeUintFromHex(const std::string& hex);

	static std::unique_ptr<CLineSegment> CreateLine(const std::vector<std::string>& args);
	static std::unique_ptr<CRectangle> CreateRectangle(const std::vector<std::string>& args);
	static std::unique_ptr<CTriangle> CreateTriangle(const std::vector<std::string>& args);
	static std::unique_ptr<CCircle> CreateCircle(const std::vector<std::string>& args);
};
