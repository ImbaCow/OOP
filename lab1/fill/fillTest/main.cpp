#include "pch.h"
#include "../fill/Field.h"

#define BOOST_TEST_MODULE FillTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(testInit)
	BOOST_AUTO_TEST_CASE(testNormalInit)
	{
		string fieldString = "O #\n##\n";
		stringstream ss(fieldString);
		Field field(ss);
		BOOST_CHECK_EQUAL(field.ToString(), fieldString);
	}


	BOOST_AUTO_TEST_CASE(testWrongChar)
	{
		string fieldString = "G #\n##\n";
		string expectedString = "  #\n##\n";

		stringstream ss(fieldString);
		Field field(ss);
		BOOST_CHECK_EQUAL(field.ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(testEmpty)
	{
		string fieldString = "\n";
		string expectedString = "\n";

		stringstream ss(fieldString);
		Field field(ss);
		BOOST_CHECK_EQUAL(field.ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(testMaxX)
	{
		string fieldString(MAX_X_SIZE * 2, BORDER_CHAR);
		string expectedString(MAX_X_SIZE, BORDER_CHAR);

		stringstream ss(fieldString);
		Field field(ss);
		BOOST_CHECK_EQUAL(field.ToString().size() - 1, expectedString.size());
	}

	BOOST_AUTO_TEST_CASE(testMaxY)
	{
		string fieldString(MAX_Y_SIZE * 2, '\n');
		string expectedString(MAX_Y_SIZE, '\n');

		stringstream ss(fieldString);
		Field field(ss);
		BOOST_CHECK_EQUAL(field.ToString().size(), expectedString.size());
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testFill)
	BOOST_AUTO_TEST_CASE(testFull)
	{
		string fieldString("O");
		string expectedString;
		for (size_t i = 0; i < MAX_Y_SIZE; ++i)
		{
			for (size_t j = 0; j < MAX_Y_SIZE; ++j)
			{
				expectedString += '-';
			}
			expectedString += '\n';
		}
		expectedString[0] = 'O';

		stringstream ss(fieldString);
		Field field(ss);
		field.Fill();
		BOOST_CHECK_EQUAL(field.ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(testBorderSmall)
	{
		string fieldString(string()
			+ "O #\n" 
			+ " #\n"
			+ "#\n");
		string expectedString(string()
			+ "O-#\n"
			+ "-#\n"
			+ "#\n");

		stringstream ss(fieldString);
		Field field(ss);
		field.Fill();
		BOOST_CHECK_EQUAL(field.ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(testBorder)
	{
		string fieldString(string() 
			+ "O  #\n"
			+ "  #\n"
			+ " #\n"
			+ "#\n");
		string expectedString(string()
			+ "O--#\n"
			+ "--#\n"
			+ "-#\n"
			+ "#\n");

		stringstream ss(fieldString);
		Field field(ss);
		field.Fill();
		BOOST_CHECK_EQUAL(field.ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(testSecondMark)
	{
		string fieldString(string() 
			+ "O  #O #\n" 
			+ "  #  #\n"
			+ " # ##\n"
			+ "#\n");
		string expectedString(string()
			+ "O--#O-#\n"
			+ "--#--#\n"
			+ "-# ##\n"
			+ "#\n");

		stringstream ss(fieldString);
		Field field(ss);
		field.Fill();
		BOOST_CHECK_EQUAL(field.ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()
