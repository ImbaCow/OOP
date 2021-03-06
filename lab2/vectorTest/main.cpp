#pragma once
#include "pch.h"
#include "../vector_6/MyArray.h"
#include "../vector_6/MyArray.cpp"
#define BOOST_TEST_MODULE TvTest
#include <boost/test/unit_test.hpp>

using namespace std;

struct ArrayFixture
{
	MyArray arr;
};

BOOST_FIXTURE_TEST_SUITE(testArray, ArrayFixture)

	BOOST_AUTO_TEST_SUITE(testProcess)

		BOOST_AUTO_TEST_CASE(testProcess1) {
			arr.AddItemsFromString("2 3 4");
			arr.ProcessArray();
			BOOST_CHECK(arr.ReturnByString() == "4.000 6.000 8.000");
		}

		BOOST_AUTO_TEST_CASE(testProcess2) {
			arr.AddItemsFromString("2.2 3.2 4.2");
			arr.ProcessArray();
			BOOST_CHECK(arr.ReturnByString() == "4.200 6.109 8.018");
		}

		BOOST_AUTO_TEST_CASE(testProcess3) {
			arr.AddItemsFromString("00.2 12.12211212 11");
			arr.ProcessArray();
			BOOST_CHECK(arr.ReturnByString() == "12.122 734.728 666.716");
		}

		BOOST_AUTO_TEST_CASE(testProcess4) {
			arr.AddItemsFromString("8.2");
			arr.ProcessArray();
			BOOST_CHECK(arr.ReturnByString() == "8.200");
		}

		BOOST_AUTO_TEST_CASE(testProcess5) {
			arr.AddItemsFromString(string());
			BOOST_CHECK_THROW(arr.ProcessArray(), exception);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testSort)

		BOOST_AUTO_TEST_CASE(testSort1) {
			arr.AddItemsFromString("4 3 2");
			arr.SortArray();
			BOOST_CHECK(arr.ReturnByString() == "2.000 3.000 4.000");
		}

		BOOST_AUTO_TEST_CASE(testSort2) {
			arr.AddItemsFromString("2.2 4.2 3.22 3.2");
			arr.SortArray();
			BOOST_CHECK(arr.ReturnByString() == "2.200 3.200 3.220 4.200");
		}

		BOOST_AUTO_TEST_CASE(testSort3) {
			arr.AddItemsFromString(string());
			BOOST_CHECK_NO_THROW(arr.SortArray());
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()