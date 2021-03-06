#include "pch.h"
#include "../complex/CComplex.cpp"
#include "../complex/CComplex.h"

#define BOOST_TEST_MODULE ComplexTest
#include <boost/test/unit_test.hpp>

#define DOUBLE_COMPARE_EPSILION 0.01

BOOST_AUTO_TEST_SUITE(testComplex)

	BOOST_AUTO_TEST_SUITE(testCreation)
		BOOST_AUTO_TEST_CASE(testNormal)
		{
			CComplex complex(3, 4);

			BOOST_CHECK_CLOSE_FRACTION(complex.Re(), 3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(complex.Im(), 4, DOUBLE_COMPARE_EPSILION);

			BOOST_CHECK_CLOSE_FRACTION(complex.GetMagnitude(), 5, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(complex.GetArgument(), 0.927, DOUBLE_COMPARE_EPSILION);
		}

		BOOST_AUTO_TEST_CASE(testReal)
		{
			CComplex complex(3);
			BOOST_CHECK_CLOSE_FRACTION(complex.Re(), 3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(complex.Im(), 0, DOUBLE_COMPARE_EPSILION);

			BOOST_CHECK_CLOSE_FRACTION(complex.GetMagnitude(), 3, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(complex.GetArgument(), 0, DOUBLE_COMPARE_EPSILION);
		}

		BOOST_AUTO_TEST_CASE(testImag)
		{
			CComplex complex(0, 4);
			BOOST_CHECK_CLOSE_FRACTION(complex.Re(), 0, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(complex.Im(), 4, DOUBLE_COMPARE_EPSILION);

			BOOST_CHECK_CLOSE_FRACTION(complex.GetMagnitude(), 4, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(complex.GetArgument(), 1.57, DOUBLE_COMPARE_EPSILION);
		}

		BOOST_AUTO_TEST_CASE(testDefault)
		{
			CComplex complex;
			BOOST_CHECK_CLOSE_FRACTION(complex.Re(), 0, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_CLOSE_FRACTION(complex.Im(), 0, DOUBLE_COMPARE_EPSILION);

			BOOST_CHECK_CLOSE_FRACTION(complex.GetMagnitude(), 0, DOUBLE_COMPARE_EPSILION);
			BOOST_CHECK_THROW(complex.GetArgument(), std::logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct ComplexExamples
	{
		CComplex resultNum;
	};
	BOOST_FIXTURE_TEST_SUITE(testOperators, ComplexExamples)

		BOOST_AUTO_TEST_SUITE(testCompare)

			BOOST_AUTO_TEST_SUITE(testEqual)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);

					resultNum = a;
					BOOST_CHECK(resultNum == a);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum = 3.0;
					BOOST_CHECK(resultNum == 3.0);
				}

				BOOST_AUTO_TEST_CASE(testSwapedDouble)
				{
					resultNum = 3.0;
					BOOST_CHECK(3.0 == resultNum);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testNotEqual)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					const CComplex negative(-3, -4);
					resultNum = a;
					BOOST_CHECK(resultNum != negative);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum = 3.0;
					BOOST_CHECK(resultNum != 4.0);
				}

				BOOST_AUTO_TEST_CASE(testSwapedDouble)
				{
					resultNum = 3.0;
					BOOST_CHECK(4.0 != resultNum);
				}
			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testStream)

			BOOST_AUTO_TEST_SUITE(testOut)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					std::stringstream ss;
					ss << CComplex{ 3, 4.8 };
					BOOST_CHECK_EQUAL(ss.str(), "3+4.8i");
				}

				BOOST_AUTO_TEST_CASE(testNegative)
				{
					std::stringstream ss;
					ss << CComplex{ -3, -4.8 };
					BOOST_CHECK_EQUAL(ss.str(), "-3-4.8i");
				}

				BOOST_AUTO_TEST_CASE(testRealNull)
				{
					std::stringstream ss;
					ss << CComplex{ 0, 3 };
					BOOST_CHECK_EQUAL(ss.str(), "3i");
				}

				BOOST_AUTO_TEST_CASE(testImagNull)
				{
					std::stringstream ss;
					ss << CComplex{ -3.2, 0 };
					BOOST_CHECK_EQUAL(ss.str(), "-3.2");
				}

				BOOST_AUTO_TEST_CASE(testNull)
				{
					std::stringstream ss;
					ss << CComplex{ 0, 0 };
					BOOST_CHECK_EQUAL(ss.str(), "0");
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testIn)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					std::stringstream ss("3+4.8i");
					BOOST_CHECK_NO_THROW(ss >> resultNum);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 4.8, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNegative)
				{
					std::stringstream ss("-3-4.8i");
					BOOST_CHECK_NO_THROW(ss >> resultNum);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -4.8, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testError1)
				{
					std::stringstream ss("3+4.8");

					BOOST_CHECK_THROW(ss >> resultNum, std::logic_error);
				}

				BOOST_AUTO_TEST_CASE(testError2)
				{
					std::stringstream ss("3 4.8i");

					BOOST_CHECK_THROW(ss >> resultNum, std::logic_error);
				}
			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testPlus)

			BOOST_AUTO_TEST_SUITE(testBinary)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = a + b;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 9, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 12, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNegative)
				{
					const CComplex a(3, 4);
					const CComplex negative(-3, -4);
					resultNum = a + negative;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 0, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testSwaped)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = b + a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 9, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 12, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					const CComplex a(3, 4);
					resultNum = a + 6.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 9, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 4, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testUnary)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					resultNum = +a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 4, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNull)
				{
					const CComplex negative(-3, -4);
					resultNum = +negative;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -4, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum = +3.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testSelf)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					resultNum += a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 4, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testReturnReference)
				{
					const CComplex a(3, 4);
					resultNum = a;
					(resultNum += resultNum) += resultNum;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 12, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 16, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum += 3.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testMinus)

			BOOST_AUTO_TEST_SUITE(testBinary)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = a - b;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -4, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testSwaped)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = b - a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 4, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNegative)
				{
					const CComplex a(3, 4);
					const CComplex negative(-3, -4);
					resultNum = a - negative;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 6, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 8, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					const CComplex a(3, 4);
					resultNum = a - 6.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 4, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testUnary)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					resultNum = -a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -4, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum = -3.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testSelf)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					resultNum -= a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -4, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testReturnReference)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = a;
					(resultNum -= b) -= resultNum;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 0, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum -= 3.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testMultipl)

			BOOST_AUTO_TEST_SUITE(testBinary)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = a * b;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -14, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 48, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNegative)
				{
					const CComplex b(6, 8);
					const CComplex negative(-3, -4);
					resultNum = negative * b;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 14, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -48, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testSwaped)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = b * a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -14, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 48, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					const CComplex a(3, 4);
					resultNum = a * 6.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 18, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 24, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testSelf)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					resultNum = { 1.0, 1.0 };
					resultNum *= a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -1, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 7, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testReturnReference)
				{
					const CComplex a(3, 4);
					resultNum = { 1.0, 1.0 };
					(resultNum *= a) *= resultNum;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -48, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -14, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum = { 1.0, 1.0 };
					resultNum *= 3.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 3, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 3, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testDiv)

			BOOST_AUTO_TEST_SUITE(testBinary)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					const CComplex b(6, 8);
					resultNum = a / b;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 0.5, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNegative)
				{
					const CComplex b(6, 8);
					const CComplex negative(-3, -4);
					resultNum = negative / b;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), -0.5, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNull)
				{
					const CComplex a(3, 4);
					const CComplex nullNum(0, 0);
					BOOST_CHECK_THROW(a / nullNum, std::logic_error);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					const CComplex a(3, 4);
					resultNum = a / 6.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 0.5, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0.666, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testSelf)
				BOOST_AUTO_TEST_CASE(testNormal)
				{
					const CComplex a(3, 4);
					resultNum = { 1.0, 1.0 };
					resultNum /= a;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 0.28, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), -0.04, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testReturnReference)
				{
					const CComplex a(3, 4);
					resultNum = { 1.0, 1.0 };
					(resultNum /= a) /= resultNum;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 1, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0, DOUBLE_COMPARE_EPSILION);
				}

				BOOST_AUTO_TEST_CASE(testNull)
				{
					const CComplex nullNum(0, 0);
					resultNum = { 1.0, 1.0 };
					BOOST_CHECK_THROW(resultNum /= nullNum, std::logic_error);
				}

				BOOST_AUTO_TEST_CASE(testDouble)
				{
					resultNum = { 1.0, 1.0 };
					resultNum /= 3.0;

					BOOST_CHECK_CLOSE_FRACTION(resultNum.Re(), 0.333, DOUBLE_COMPARE_EPSILION);
					BOOST_CHECK_CLOSE_FRACTION(resultNum.Im(), 0.333, DOUBLE_COMPARE_EPSILION);
				}
			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
