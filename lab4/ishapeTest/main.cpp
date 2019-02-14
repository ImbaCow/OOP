#pragma once
#include "pch.h"
#include "../ishape/ShapeFactory.h"
#include "../ishape/ShapeFactory.cpp"

#include "../ishape/CCircle.cpp"
#include "../ishape/CLineSegment.cpp"
#include "../ishape/CPoint.cpp"
#include "../ishape/CRectangle.cpp"
#include "../ishape/CTriangle.cpp"
#include "../ishape/IShape.cpp"
#include "../ishape/ISolidShape.cpp"

#include "../ishape/IShapeArray.h"
#include "../ishape/IShapeArray.cpp"

#define BOOST_TEST_MODULE ShapeTest
#include <boost/test/unit_test.hpp>

#define DOUBLE_COMPARE_EPSILION 0.01

BOOST_AUTO_TEST_SUITE(testShapeCreation)

	BOOST_AUTO_TEST_SUITE(testCreation)
		BOOST_AUTO_TEST_CASE(testCreateCircle)
		{
			std::string circleInfoString = "circle 1.1 2.2 3 ffffff 000000";
			IShape * shape = ShapeFactory::GetShape(circleInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "circle 1.100000 2.200000 3.000000 16777215 0");
			delete shape;
		}
		BOOST_AUTO_TEST_CASE(testCreateLine)
		{
			std::string lineInfoString = "line 1.1 2.2 3.3 4.4 ffffff";
			IShape * shape = ShapeFactory::GetShape(lineInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "line 1.100000 2.200000 3.300000 4.400000 16777215");
			delete shape;
		}
		BOOST_AUTO_TEST_CASE(testCreateTriangle)
		{
			std::string triangleInfoString = "triangle 1.1 2.2 3.3 4.4 5.5 6.6 ffffff 000000";
			IShape * shape = ShapeFactory::GetShape(triangleInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "triangle 1.100000 2.200000 3.300000 4.400000 5.500000 6.600000 16777215 0");
			delete shape;
		}
		BOOST_AUTO_TEST_CASE(testCreateRectangle)
		{
			std::string rectangleInfoString = "rectangle 1.1 2.2 3 4 ffffff 000000";
			IShape * shape = ShapeFactory::GetShape(rectangleInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "rectangle 1.100000 2.200000 3.000000 4.000000 16777215 0");
			delete shape;
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testCreationError)
		BOOST_AUTO_TEST_CASE(testCreationErrorShape)
		{
			std::string rectangleInfoString = "rect 1.1 2.2 3 4 ffffff 000000";
			BOOST_CHECK_THROW(ShapeFactory::GetShape(rectangleInfoString), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testEmptyShapeError)
		{
			BOOST_CHECK_THROW(ShapeFactory::GetShape(""), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testCreationErrorArgument)
		{
			std::string rectangleInfoString = "rectangle 1.1 2.2 3 four ffffff 000000";
			BOOST_CHECK_THROW(ShapeFactory::GetShape(rectangleInfoString), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testCreationErrorArgumentCount)
		{
			std::string rectangleInfoString = "rectangle 1.1 2.2 3 4 ffffff";
			BOOST_CHECK_THROW(ShapeFactory::GetShape(rectangleInfoString), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testShapes)

	struct CircleFixture
	{
		CCircle * circle = nullptr;
		~CircleFixture()
		{
			if (circle != nullptr)
			{
				delete circle;
			}
		}
	};
	
	BOOST_FIXTURE_TEST_SUITE(testCircle, CircleFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			std::vector<std::string> args = {
				"circle",
				"1.1",
				"2.2",
				"3",
				"ffffff",
				"000000"
			};
			circle = new CCircle(args);
			BOOST_CHECK_CLOSE_FRACTION(circle->GetCenter().x, 1.1,  DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(circle->GetCenter().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(circle->GetRadius(), 3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(circle->GetOutlineColor(), 16777215);
			BOOST_CHECK_EQUAL(circle->GetFillColor(), 0);
		}
		BOOST_AUTO_TEST_CASE(testErrorInit)
		{
			std::vector<std::string> args = {
				"circle",
				"1.1",
				"ffffff",
				"000000"
			};
			BOOST_CHECK_THROW(circle = new CCircle(args), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testNegativeInit)
		{
			std::vector<std::string> args = {
				"circle",
				"1.1",
				"2.2",
				"-3",
				"ffffff",
				"000000"
			};
			BOOST_CHECK_THROW(circle = new CCircle(args), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				std::vector<std::string> args = {
					"circle",
					"1.1",
					"2.2",
					"3",
					"ffffff",
					"000000"
				};
				circle = new CCircle(args);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetArea(), 28.2743, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetPerimeter(), 18.852, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				std::vector<std::string> args = {
					"circle",
					"1.1",
					"2.2",
					"0",
					"ffffff",
					"000000"
				};
				circle = new CCircle(args);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetPerimeter(), 0, DOUBLE_COMPARE_EPSILION);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct LineFixture
	{
		CLineSegment * line = nullptr;
		~LineFixture()
		{
			if (line != nullptr)
			{
				delete line;
			}
		}
	};

	BOOST_FIXTURE_TEST_SUITE(testLine, LineFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			std::vector<std::string> args = {
				"line",
				"1.1",
				"2.2",
				"3.3",
				"4.4",
				"ffffff"
			};
			line = new CLineSegment(args);
			BOOST_CHECK_CLOSE_FRACTION(line->GetStartPoint().x, 1.1, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(line->GetStartPoint().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(line->GetEndPoint().x, 3.3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(line->GetEndPoint().y, 4.4, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(line->GetOutlineColor(), 16777215);
		}
		BOOST_AUTO_TEST_CASE(testErrorInit)
		{
			std::vector<std::string> args = {
				"line",
				"1.1",
				"2.2",
				"ffffff"
			};
			BOOST_CHECK_THROW(line = new CLineSegment(args), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				std::vector<std::string> args = {
					"line",
					"1.1",
					"2.2",
					"3.3",
					"4.4",
					"ffffff"
				};
				line = new CLineSegment(args);
				BOOST_CHECK_CLOSE_FRACTION(line->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(line->GetPerimeter(), 6.2225, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				std::vector<std::string> args = {
					"line",
					"1.1",
					"2.2",
					"1.1",
					"2.2",
					"ffffff"
				};
				line = new CLineSegment(args);
				BOOST_CHECK_CLOSE_FRACTION(line->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(line->GetPerimeter(), 0, DOUBLE_COMPARE_EPSILION);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct RectangleFixture
	{
		CRectangle * rectangle = nullptr;
		~RectangleFixture()
		{
			if (rectangle != nullptr)
			{
				delete rectangle;
			}
		}
	};

		BOOST_FIXTURE_TEST_SUITE(testRectangle, RectangleFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			std::vector<std::string> args = {
				"rectangle",
				"1.1",
				"2.2",
				"3",
				"4",
				"ffffff",
				"000000"
			};
			rectangle = new CRectangle(args);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetLeftTop().x, 1.1, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetLeftTop().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetWidth(), 3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetHeight(), 4,  DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(rectangle->GetOutlineColor(), 16777215);
			BOOST_CHECK_EQUAL(rectangle->GetFillColor(), 0);
		}
		BOOST_AUTO_TEST_CASE(testErrorInit)
		{
			std::vector<std::string> args = {
				"rectangle",
				"1.1",
				"3",
				"ffffff",
				"000000"
			};
			BOOST_CHECK_THROW(rectangle = new CRectangle(args), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testNegativeInit)
		{
			std::vector<std::string> args = {
				"rectangle",
				"1.1",
				"2.2",
				"-3",
				"-4",
				"ffffff",
				"000000"
			};
			BOOST_CHECK_THROW(rectangle = new CRectangle(args), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				std::vector<std::string> args = {
					"rectangle",
					"1.1",
					"2.2",
					"3",
					"4",
					"ffffff",
					"000000"
				};
				rectangle = new CRectangle(args);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetArea(), 12, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetPerimeter(), 14, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				std::vector<std::string> args = {
					"rectangle",
					"1.1",
					"2.2",
					"0",
					"4",
					"ffffff",
					"000000"
				};
				rectangle = new CRectangle(args);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetPerimeter(), 8, DOUBLE_COMPARE_EPSILION);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct TriangleFixture
	{
		CTriangle * triangle = nullptr;
		~TriangleFixture()
		{
			if (triangle != nullptr)
			{
				delete triangle;
			}
		}
	};

	BOOST_FIXTURE_TEST_SUITE(testTtrangle, TriangleFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			std::vector<std::string> args = {
				"triangle",
				"1.1",
				"2.2",
				"3.3",
				"4.4",
				"5.5",
				"6.6",
				"ffffff",
				"000000"
			};
			triangle = new CTriangle(args);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex1().x, 1.1, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex1().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex2().x, 3.3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex2().y, 4.4, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex3().x, 5.5, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex3().y, 6.6, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(triangle->GetOutlineColor(), 16777215);
			BOOST_CHECK_EQUAL(triangle->GetFillColor(), 0);
		}
		BOOST_AUTO_TEST_CASE(testErrorInit)
		{
			std::vector<std::string> args = {
				"triangle",
				"1.1",
				"2.2",
				"3.3",
				"4.4",
				"ffffff",
				"000000"
			};
			BOOST_CHECK_THROW(triangle = new CTriangle(args), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				std::vector<std::string> args = {
					"triangle",
					"1.1",
					"2.2",
					"3.3",
					"4.4",
					"5.5",
					"2.2",
					"ffffff",
					"000000"
				};
				triangle = new CTriangle(args);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetArea(), 4.84, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetPerimeter(), 10.62254, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				std::vector<std::string> args = {
					"triangle",
					"1.1",
					"2.2",
					"1.1",
					"2.2",
					"1.1",
					"2.2",
					"ffffff",
					"000000"
				};
				triangle = new CTriangle(args);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetPerimeter(), 0, DOUBLE_COMPARE_EPSILION);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testShapeArr)
	BOOST_AUTO_TEST_SUITE(testArrCreation)
		BOOST_AUTO_TEST_CASE(testCreation)
		{
			std::stringstream ss;
			ss << "circle 1.1 2.2 3 ffffff 000000" << std::endl
				<< "line 1.1 2.2 3.3 4.4 ffffff" << std::endl
				<< "triangle 1.1 2.2 3.3 4.4 5.5 6.6 ffffff 000000" << std::endl
				<< "rectangle 1.1 2.2 3 4 ffffff 000000" << std::endl;

			std::string expected = std::string() + "circle 1.100000 2.200000 3.000000 16777215 0\n" +
				"line 1.100000 2.200000 3.300000 4.400000 16777215\n" +
				"triangle 1.100000 2.200000 3.300000 4.400000 5.500000 6.600000 16777215 0\n" +
				"rectangle 1.100000 2.200000 3.000000 4.000000 16777215 0\n";

			IShapeArray shapeArr(ss);
			BOOST_CHECK_EQUAL(shapeArr.ToString(), expected);
		}
		BOOST_AUTO_TEST_CASE(testEmptyCreation)
		{
			std::stringstream ss;

			IShapeArray shapeArr(ss);
			BOOST_CHECK(shapeArr.ToString().empty());
		}
		BOOST_AUTO_TEST_CASE(testErrorCreation)
		{
			std::stringstream ss;
			ss << "circle 1.1 2.2 3 ffffff 000000" << std::endl
				<< "line 1.1 2.2 4 ffffff" << std::endl
				<< "triangle 1.1 2.2 3.3 4.4 5.5 6.6 ffffff 000000" << std::endl
				<< "rectangle 1.1 2.2 3 4 ffffff 000000" << std::endl;

			BOOST_CHECK_THROW(IShapeArray shapeArr(ss), std::exception);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testArrProcess)
		BOOST_AUTO_TEST_CASE(testFindMaxAreaMinPerimeter)
		{
			std::stringstream ss;
			ss << "circle 1.1 2.2 3 ffffff 000000" << std::endl
				<< "line 1.1 2.2 3.3 4.4 ffffff" << std::endl
				<< "triangle 1.1 2.2 3.3 4.4 5.5 6.6 ffffff 000000" << std::endl
				<< "rectangle 1.1 2.2 3 4 ffffff 000000" << std::endl;

			IShapeArray shapeArr(ss);
			std::pair<IShape *, IShape *> maxAreaMinPerimeter = shapeArr.GetMaxAreaMinPerimeter();

			BOOST_CHECK_CLOSE_FRACTION(maxAreaMinPerimeter.first->GetArea(), 28.2743, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(maxAreaMinPerimeter.second->GetPerimeter(), 6.22254, DOUBLE_COMPARE_EPSILION);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
