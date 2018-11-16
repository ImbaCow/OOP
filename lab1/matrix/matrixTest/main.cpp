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
	SquareMatrix3 matrix;
};

BOOST_FIXTURE_TEST_SUITE(testMatrix, MatrixFixture)

	BOOST_AUTO_TEST_SUITE(matrixInitTest)
	
		BOOST_AUTO_TEST_CASE(matrixTest1)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.SetMatrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
				matrix.WriteMainMatr();
			}
			BOOST_CHECK(output.is_equal("1.000 2.000 3.000 \n4.000 5.000 6.000 \n7.000 8.000 9.000 \n"));
		}

		BOOST_AUTO_TEST_CASE(matrixTest2)
		{
			BOOST_CHECK_THROW(matrix.SetMatrix({ {1, 2, 3, 4}, {4, 5, 6, 7}, {1, 2, 8, 9} }) , std::exception);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(matrixDetTest)

		BOOST_AUTO_TEST_CASE(matrixDetTest1)
		{
			matrix.SetMatrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
			BOOST_CHECK(matrix.GetDet() == 0.0);
		}
		BOOST_AUTO_TEST_CASE(matrixDetTest2)
		{
			matrix.SetMatrix({ {1, 2, 3}, {4, 5, 6}, {7, 9, 9} });
			BOOST_CHECK(matrix.GetDet() == 6.0);
		}
		BOOST_AUTO_TEST_CASE(matrixDetTest3)
		{
			matrix.SetMatrix({ {12, 2, 3}, {4, 5, 6}, {7, 9, 9} });
			BOOST_CHECK(matrix.GetDet() == -93.0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(matrixAdjugateTest)

		BOOST_AUTO_TEST_CASE(matrixAdjugateTest1)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.SetMatrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
				matrix.WriteAdjugateMatr();
			}
			BOOST_CHECK(output.is_equal("-3.000 6.000 -3.000 \n6.000 -12.000 6.000 \n-3.000 6.000 -3.000 \n"));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(matrixTest)

		BOOST_AUTO_TEST_CASE(matrixTransposeTest1)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.SetMatrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
				matrix.WriteTransposeMatr();
			}
			BOOST_CHECK(output.is_equal("1.000 4.000 7.000 \n2.000 5.000 8.000 \n3.000 6.000 9.000 \n"));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(matrixTest)

		BOOST_AUTO_TEST_CASE(matrixInvertTest1)
		{
			matrix.SetMatrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
			BOOST_CHECK_THROW(matrix.WriteInvertMatr(), std::exception);
		}
		BOOST_AUTO_TEST_CASE(matrixInvertTest2)
		{
			boost::test_tools::output_test_stream output;
			{
				cout_redirect guard(output.rdbuf());
				matrix.SetMatrix({ {1, 2, 3}, {4, 5, 6}, {7, 9, 9} });
				matrix.WriteInvertMatr();
			}
			BOOST_CHECK(output.is_equal("-1.500 1.500 -0.500 \n1.000 -2.000 1.000 \n0.167 0.833 -0.500 \n"));
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()