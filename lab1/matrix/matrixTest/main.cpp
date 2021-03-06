#include "pch.h"
#include "../matrix/Matrix.h"
#include "../matrix/Matrix.cpp"
#define BOOST_TEST_MODULE MatrixTest
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>


struct cout_redirect {
	cout_redirect(std::streambuf * new_buffer)
		: old(std::cout.rdbuf(new_buffer))
	{
	}
	~cout_redirect() {
		std::cout.rdbuf(old);
	}
private:
	std::streambuf * old;
};

struct MatrixFixture {
	SquareMatrix matrix;
};

BOOST_FIXTURE_TEST_SUITE(testMatrix, MatrixFixture)

	BOOST_AUTO_TEST_SUITE(matrixInitTest)
	
		BOOST_AUTO_TEST_CASE(matrixTestInitValues)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.WriteMatr(std::cout);
			}
			BOOST_CHECK(output.is_equal("0.000 0.000 0.000 \n0.000 0.000 0.000 \n0.000 0.000 0.000 \n"));
		}

		BOOST_AUTO_TEST_CASE(matrixTestInitDet)
		{
			BOOST_CHECK(matrix.GetDeterminant() == 0);
		}

		BOOST_AUTO_TEST_CASE(matrixTestInitInvert)
		{
			BOOST_CHECK_THROW(matrix.Invert(), std::exception);
		}

		BOOST_AUTO_TEST_CASE(matrixTestInitAdjugate)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.FindAdjugate()->WriteMatr(std::cout);
			}
			BOOST_CHECK(output.is_equal("0.000 -0.000 0.000 \n-0.000 0.000 -0.000 \n0.000 -0.000 0.000 \n"));
		}

		BOOST_AUTO_TEST_CASE(matrixTestInitTranspose)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.Transpose()->WriteMatr(std::cout);
			}
			BOOST_CHECK(output.is_equal("0.000 0.000 0.000 \n0.000 0.000 0.000 \n0.000 0.000 0.000 \n"));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(matrixInitTest)

		BOOST_AUTO_TEST_CASE(matrixInitTest1)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.SetFromMatr({ {1, 2, 3, 4, 5, 6, 7, 8, 9} });
				matrix.WriteMatr(std::cout);
			}
			BOOST_CHECK(output.is_equal("1.000 2.000 3.000 \n4.000 5.000 6.000 \n7.000 8.000 9.000 \n"));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(matrixDeterminantTest)

		BOOST_AUTO_TEST_CASE(matrixDetTest1)
		{
			matrix.SetFromMatr({ {1, 2, 3, 4, 5, 6, 7, 8, 9} });
			BOOST_CHECK(matrix.GetDeterminant() == 0.0);
		}
		BOOST_AUTO_TEST_CASE(matrixDetTest2)
		{
			matrix.SetFromMatr({ {1, 2, 3, 4, 5, 6, 7, 9, 9} });
			BOOST_CHECK(matrix.GetDeterminant() == 6.0);
		}
		BOOST_AUTO_TEST_CASE(matrixDetTest3)
		{
			matrix.SetFromMatr({ {12, 2, 3, 4, 5, 6, 7, 9, 9} });
			BOOST_CHECK(matrix.GetDeterminant() == -93.0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct MatrixFixtureInit : MatrixFixture
	{
		MatrixFixtureInit()
		{
			matrix.SetFromMatr({ {1, 2, 3, 4, 5, 6, 7, 8, 9} });
		}
	};

	BOOST_FIXTURE_TEST_SUITE(testMatrixInit, MatrixFixtureInit)

		BOOST_AUTO_TEST_SUITE(matrixAdjugateTest)

			BOOST_AUTO_TEST_CASE(matrixAdjugateTest1)
			{
				boost::test_tools::output_test_stream output;
				{
					cout_redirect guard(output.rdbuf());
					matrix.FindAdjugate()->WriteMatr(std::cout);
				}
				BOOST_CHECK(output.is_equal("-3.000 6.000 -3.000 \n6.000 -12.000 6.000 \n-3.000 6.000 -3.000 \n"));
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(matrixTransposeTest)

			BOOST_AUTO_TEST_CASE(matrixTransposeTest1)
			{
				boost::test_tools::output_test_stream output;
				{
					cout_redirect guard(output.rdbuf());
					matrix.Transpose()->WriteMatr(std::cout);
				}
				BOOST_CHECK(output.is_equal("1.000 4.000 7.000 \n2.000 5.000 8.000 \n3.000 6.000 9.000 \n"));
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(matrixInvertTest)

			BOOST_AUTO_TEST_CASE(matrixInvertTest1)
			{
				BOOST_CHECK_THROW(matrix.Invert(), std::exception);
			}
			BOOST_AUTO_TEST_CASE(matrixInvertTest2)
			{
				boost::test_tools::output_test_stream output;
				{
					cout_redirect guard(output.rdbuf());
					matrix.SetFromMatr({ {1, 2, 3, 4, 5, 6, 7, 9, 9} });
					matrix.Invert()->WriteMatr(std::cout);
				}
				BOOST_CHECK(output.is_equal("-1.500 1.500 -0.500 \n1.000 -2.000 1.000 \n0.167 0.833 -0.500 \n"));
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()