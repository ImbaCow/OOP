#pragma once
#include "pch.h"

#include "../shape/CCircle.h"
#include "../shape/CLineSegment.h"
#include "../shape/CPoint.h"
#include "../shape/CRectangle.h"
#include "../shape/CTriangle.h"
#include "../shape/IShape.h"
#include "../shape/ShapeFactory.h"
#include "../shape/ShapeArray.h"
#include "../shape/CShape.h"
#include "../shape/CSolidShape.h"

#define BOOST_TEST_MODULE ShapeTest
#include <boost/test/unit_test.hpp>

#define DOUBLE_COMPARE_EPSILION 0.01

BOOST_AUTO_TEST_SUITE(testShapeCreation)

	BOOST_AUTO_TEST_SUITE(testCreation)
		BOOST_AUTO_TEST_CASE(testCreateCircle)
		{
			std::string circleInfoString = "circle 1.1 2.2 3 ffffff 000000";
			std::unique_ptr<IShape> shape = CreateShape(circleInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "circle 1.100000 2.200000 3.000000 16777215 0");
		}
		BOOST_AUTO_TEST_CASE(testCreateLine)
		{
			std::string lineInfoString = "line 1.1 2.2 3.3 4.4 ffffff";
			std::unique_ptr<IShape> shape = CreateShape(lineInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "line 1.100000 2.200000 3.300000 4.400000 16777215");
		}
		BOOST_AUTO_TEST_CASE(testCreateTriangle)
		{
			std::string triangleInfoString = "triangle 1.1 2.2 3.3 4.4 5.5 6.6 ffffff 000000";
			std::unique_ptr<IShape> shape = CreateShape(triangleInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "triangle 1.100000 2.200000 3.300000 4.400000 5.500000 6.600000 16777215 0");
		}
		BOOST_AUTO_TEST_CASE(testCreateRectangle)
		{
			std::string rectangleInfoString = "rectangle 1.1 2.2 3 4 ffffff 000000";
			std::unique_ptr<IShape> shape = CreateShape(rectangleInfoString);
			BOOST_CHECK_EQUAL(shape->ToString(), "rectangle 1.100000 2.200000 3.000000 4.000000 16777215 0");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testCreationError)
		BOOST_AUTO_TEST_CASE(testCreationErrorShape)
		{
			std::string rectangleInfoString = "rect 1.1 2.2 3 4 ffffff 000000";
			BOOST_CHECK_THROW(CreateShape(rectangleInfoString), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testEmptyShapeError)
		{
			BOOST_CHECK_THROW(CreateShape(""), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testCreationErrorArgument)
		{
			std::string rectangleInfoString = "rectangle 1.1 2.2 3 four ffffff 000000";
			BOOST_CHECK_THROW(CreateShape(rectangleInfoString), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testCreationErrorArgumentCount)
		{
			std::string rectangleInfoString = "rectangle 1.1 2.2 3 4 ffffff";
			BOOST_CHECK_THROW(CreateShape(rectangleInfoString), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testShapes)

	struct CircleFixture
	{
		std::unique_ptr<CCircle> circle = nullptr;
	};

	BOOST_FIXTURE_TEST_SUITE(testCircle, CircleFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			circle = std::make_unique<CCircle>(CPoint{ 1.1, 2.2 }, 3, 16777215, 0);
			BOOST_CHECK_CLOSE_FRACTION(circle->GetCenter().x, 1.1, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(circle->GetCenter().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(circle->GetRadius(), 3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(circle->GetOutlineColor(), 0);
			BOOST_CHECK_EQUAL(circle->GetFillColor(), 16777215);
		}
		BOOST_AUTO_TEST_CASE(testNegativeInit)
		{
			BOOST_CHECK_THROW(std::unique_ptr<CCircle>(new CCircle(CPoint{ 1.1, 2.2 }, -3, 16777215, 0)), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				circle = std::make_unique<CCircle>(CPoint{ 1.1, 2.2 }, 3, 16777215, 0);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetArea(), 28.2743, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetPerimeter(), 18.852, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				circle = std::make_unique<CCircle>(CPoint{ 1.1, 2.2 }, 0, 16777215, 0);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(circle->GetPerimeter(), 0, DOUBLE_COMPARE_EPSILION);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct LineFixture
	{
		std::unique_ptr<CLineSegment> line = nullptr;
	};

	BOOST_FIXTURE_TEST_SUITE(testLine, LineFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			line = std::make_unique<CLineSegment>(CPoint{ 1.1, 2.2 }, CPoint{ 3.3, 4.4 }, 16777215);
			BOOST_CHECK_CLOSE_FRACTION(line->GetStartPoint().x, 1.1, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(line->GetStartPoint().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(line->GetEndPoint().x, 3.3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(line->GetEndPoint().y, 4.4, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(line->GetOutlineColor(), 16777215);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				line = std::make_unique<CLineSegment>(CPoint{ 1.1, 2.2 }, CPoint{ 3.3, 4.4 }, 16777215);
				BOOST_CHECK_CLOSE_FRACTION(line->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(line->GetPerimeter(), 6.2225, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				line = std::make_unique<CLineSegment>(CPoint{ 1.1, 2.2 }, CPoint{ 1.1, 2.2 }, 16777215);
				BOOST_CHECK_CLOSE_FRACTION(line->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(line->GetPerimeter(), 0, DOUBLE_COMPARE_EPSILION);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct RectangleFixture
	{
		std::unique_ptr<CRectangle> rectangle = nullptr;
	};

	BOOST_FIXTURE_TEST_SUITE(testRectangle, RectangleFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			rectangle = std::make_unique<CRectangle>(CPoint{ 1.1, 2.2 }, 3, 4, 16777215, 0);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetLeftTop().x, 1.1, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetLeftTop().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetHeight(), 3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(rectangle->GetWidth(), 4, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(rectangle->GetOutlineColor(), 0);
			BOOST_CHECK_EQUAL(rectangle->GetFillColor(), 16777215);
		}
		BOOST_AUTO_TEST_CASE(testNegativeInit)
		{
			BOOST_CHECK_THROW(std::unique_ptr<CRectangle>(new CRectangle(CPoint{ 1.1, 2.2 }, -3, 4, 16777215, 0)), std::invalid_argument);
			BOOST_CHECK_THROW(std::unique_ptr<CRectangle>(new CRectangle(CPoint{ 1.1, 2.2 }, 3, -4, 16777215, 0)), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				rectangle = std::make_unique<CRectangle>(CPoint{ 1.1, 2.2 }, 3, 4, 16777215, 0);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetArea(), 12, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetPerimeter(), 14, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				rectangle = std::make_unique<CRectangle>(CPoint{ 1.1, 2.2 }, 0, 4, 16777215, 0);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(rectangle->GetPerimeter(), 8, DOUBLE_COMPARE_EPSILION);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct TriangleFixture
	{
		std::unique_ptr<CTriangle> triangle = nullptr;
	};

	BOOST_FIXTURE_TEST_SUITE(testTtrangle, TriangleFixture)
		BOOST_AUTO_TEST_CASE(testInit)
		{
			triangle = std::make_unique<CTriangle>(CPoint{ 1.1, 2.2 }, CPoint{ 3.3, 4.4 }, CPoint{ 5.5, 6.6 }, 16777215, 0);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex1().x, 1.1, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex1().y, 2.2, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex2().x, 3.3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex2().y, 4.4, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex3().x, 5.5, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(triangle->GetVertex3().y, 6.6, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_EQUAL(triangle->GetOutlineColor(), 0);
			BOOST_CHECK_EQUAL(triangle->GetFillColor(), 16777215);
		}

		BOOST_AUTO_TEST_SUITE(testMath)
			BOOST_AUTO_TEST_CASE(testArea)
			{
				triangle = std::make_unique<CTriangle>(CPoint{ 1.1, 2.2 }, CPoint{ 3.3, 4.4 }, CPoint{ 5.5, 2.2 }, 16777215, 0);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetArea(), 4.84, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetPerimeter(), 10.62254, DOUBLE_COMPARE_EPSILION);
			}
			BOOST_AUTO_TEST_CASE(testNullArea)
			{
				triangle = std::make_unique<CTriangle>(CPoint{ 1.1, 2.2 }, CPoint{ 3.3, 4.4 }, CPoint{ 5.5, 6.6 }, 16777215, 0);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetArea(), 0, DOUBLE_COMPARE_EPSILION);
				BOOST_CHECK_CLOSE_FRACTION(triangle->GetPerimeter(), 12.445, DOUBLE_COMPARE_EPSILION);
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

			std::string expected = std::string() + "circle 1.100000 2.200000 3.000000 16777215 0\n" + "line 1.100000 2.200000 3.300000 4.400000 16777215\n" + "triangle 1.100000 2.200000 3.300000 4.400000 5.500000 6.600000 16777215 0\n" + "rectangle 1.100000 2.200000 3.000000 4.000000 16777215 0\n";

			auto shapeArr = GetShapeArrayFromStream(ss);
			BOOST_CHECK_EQUAL(ShapeArrayToString(shapeArr), expected);
		}
		BOOST_AUTO_TEST_CASE(testErrorCreation)
		{
			std::stringstream ss;
			ss << "circle 1.1 2.2 3 ffffff 000000" << std::endl
			   << "line 1.1 2.2 4 ffffff" << std::endl
			   << "triangle 1.1 2.2 3.3 4.4 5.5 6.6 ffffff 000000" << std::endl
			   << "rectangle 1.1 2.2 3 4 ffffff 000000" << std::endl;

			BOOST_CHECK_THROW(GetShapeArrayFromStream(ss), std::exception);
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

			auto shapeArr = GetShapeArrayFromStream(ss);
			auto maxAreaMinPerimeter = GetMaxAreaMinPerimeterShapes(shapeArr);

			BOOST_CHECK_CLOSE_FRACTION(maxAreaMinPerimeter.maxAreaShape.area, 28.2743, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(maxAreaMinPerimeter.minPerimeterShape.perimeter, 6.22254, DOUBLE_COMPARE_EPSILION);
		}
		BOOST_AUTO_TEST_CASE(testFindMaxAreaMinPerimeterSingleShape)
		{
			std::stringstream ss;
			ss << "circle 1.1 2.2 0 ffffff 000000" << std::endl;

			auto shapeArr = GetShapeArrayFromStream(ss);
			auto maxAreaMinPerimeter = GetMaxAreaMinPerimeterShapes(shapeArr);

			BOOST_CHECK_CLOSE_FRACTION(maxAreaMinPerimeter.maxAreaShape.area, 0, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(maxAreaMinPerimeter.minPerimeterShape.perimeter, 0, DOUBLE_COMPARE_EPSILION);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
