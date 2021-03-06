#pragma once
#include "pch.h"
#include "../CMyArray/CMyArray.h"
#include "../CMyArray/CMyArray.cpp"

#define BOOST_TEST_MODULE MyArrayTest
#include <boost/test/unit_test.hpp>

struct HumanContact
{
	std::string fullName;
	std::string phone;
	std::string email;
};

BOOST_AUTO_TEST_SUITE(testContructors)
	BOOST_AUTO_TEST_CASE(testBase)
	{
		CMyArray<int> arr;
		BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
	}
	BOOST_AUTO_TEST_CASE(testPointer)
	{
		int intArr[] = { 1, 2, 3 };
		CMyArray<int> arr(intArr, 3);

		BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
	}
	BOOST_AUTO_TEST_CASE(testCopy)
	{
		int intArr[] = { 1, 2 };
		CMyArray<int> arr1(intArr, 2);
		CMyArray<int> arr2(arr1);

		BOOST_CHECK_EQUAL(arr1.GetSize(), 2u);
		BOOST_CHECK_EQUAL(arr2.GetSize(), 2u);
	}
	BOOST_AUTO_TEST_CASE(testMove)
	{
		int intArr[] = { 1, 2, 3, 4 };
		CMyArray<int> arr(CMyArray<int>(intArr, 4));

		BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
	}
BOOST_AUTO_TEST_SUITE_END()

struct MyArrayFixture
{
	MyArrayFixture()
	{
		int intArr[] = { 1, 2, 3, 4 };
		filledArr = CMyArray<int>(intArr, 4);
	}

	CMyArray<int> filledArr;
};

BOOST_FIXTURE_TEST_SUITE(testMethods, MyArrayFixture)

	BOOST_AUTO_TEST_CASE(testBrackets)
	{
		BOOST_CHECK_EQUAL(filledArr[0], 1);
		BOOST_CHECK_EQUAL(filledArr[2], 3);
		BOOST_CHECK_THROW(filledArr[5], std::out_of_range);
	}
	BOOST_AUTO_TEST_CASE(testPush)
	{
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 4u);
		filledArr.Push(1);
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 5u);
		BOOST_CHECK_EQUAL(filledArr[4], 1);
	}
	BOOST_AUTO_TEST_CASE(testResize)
	{
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 4u);
		filledArr.Resize(6);
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 6u);
		BOOST_CHECK_EQUAL(filledArr[4], int());
	}
	BOOST_AUTO_TEST_CASE(testClear)
	{
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 4u);
		filledArr.Clear();
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 0u);
	}
	BOOST_AUTO_TEST_CASE(testCopy)
	{
		int intArr[] = { 4, 3, 2, 1, 0 };
		CMyArray<int> arr(intArr, 5);
		filledArr = arr;
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 5u);
		BOOST_CHECK_EQUAL(filledArr[3], 1);
	}
	BOOST_AUTO_TEST_CASE(testMove)
	{
		int intArr[] = { 4, 3, 2, 1, 0 };
		CMyArray<int> arr(CMyArray<int>(intArr, 5));
		filledArr = std::move(arr);
		BOOST_CHECK_EQUAL(filledArr.GetSize(), 5u);
		BOOST_CHECK_EQUAL(filledArr[3], 1);
	}
	BOOST_AUTO_TEST_CASE(testCustomType)
	{
		HumanContact humanArr[] = { { "Common name", "8921822", "e.e@e.e" }, { "Common name 2", "8921821", "d.d@d.d" }, { "Common name 3", "89218221", "dd.dd@dd.dd" } };
		CMyArray<HumanContact> arr(humanArr, 3);

		BOOST_CHECK_EQUAL(arr[0].fullName, "Common name");
		BOOST_CHECK_EQUAL(arr[1].phone, "8921821");
		BOOST_CHECK_EQUAL(arr[2].email, "dd.dd@dd.dd");
		BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
	}
	BOOST_AUTO_TEST_CASE(testOutOfRange)
	{
		HumanContact humanArr[] = { { "Common name", "8921822", "e.e@e.e" }, { "Common name 2", "8921821", "d.d@d.d" }, { "Common name 3", "89218221", "dd.dd@dd.dd" } };
		CMyArray<HumanContact> arr(humanArr, 3);

		BOOST_CHECK_THROW(arr[3], std::out_of_range);
	}

BOOST_AUTO_TEST_SUITE_END()

struct IteratorFixture
{
	IteratorFixture()
	{
		int intArr[]{ 1, 2, 3, 4, 5 };
		arr = CMyArray<int>(intArr, 5);
	}

	CMyArray<int> arr;
};

BOOST_FIXTURE_TEST_SUITE(testIterators, IteratorFixture)
	BOOST_AUTO_TEST_CASE(testBegins)
	{
		BOOST_CHECK_EQUAL(*arr.begin(), 1);
		BOOST_CHECK(!(*arr.begin() == 5));
		BOOST_CHECK_EQUAL(*arr.rbegin(), 5);
		BOOST_CHECK(!(*arr.rbegin() == 1));
	}
	BOOST_AUTO_TEST_CASE(testEnds)
	{
		BOOST_CHECK_EQUAL(*(arr.end() - 1), 5);
		BOOST_CHECK(!(*(arr.begin() - 1) == 1));
		BOOST_CHECK_EQUAL(*(arr.rend() - 1), 1);
		BOOST_CHECK(!(*(arr.rbegin() - 1) == 5));
	}
	BOOST_AUTO_TEST_CASE(testStraight)
	{
		std::string str;
		for (auto it = arr.begin(); it != arr.end(); ++it)
		{
			str += std::to_string(*it) + ' ';
		}
		BOOST_CHECK_EQUAL(str, std::string("1 2 3 4 5 "));
	}
	BOOST_AUTO_TEST_CASE(testReferse)
	{
		std::string str;
		for (auto it = arr.rbegin(); it != arr.rend(); ++it)
		{
			str += std::to_string(*it) + ' ';
		}
		BOOST_CHECK_EQUAL(str, std::string("5 4 3 2 1 "));
	}
BOOST_AUTO_TEST_SUITE_END()
