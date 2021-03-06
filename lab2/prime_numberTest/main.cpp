#include "pch.h"
#include "../prime_number/PrimeNumberUtils.h"

#define BOOST_TEST_MODULE PrimeTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(testGeneratePrimeNumber)
	BOOST_AUTO_TEST_CASE(testGenerate1)
	{
		std::set<int> primeSet = GeneratePrimeNumbersSet(2); //2
		BOOST_CHECK_EQUAL(primeSet.size(), 1u);
		BOOST_CHECK_EQUAL(primeSet.count(2), 1u);
	}

	BOOST_AUTO_TEST_CASE(testGenerate2)
	{
		std::set<int> primeSet = GeneratePrimeNumbersSet(11); //2,3,5,7,11
		BOOST_CHECK_EQUAL(primeSet.size(), 5u);
		BOOST_CHECK_EQUAL(primeSet.count(2), 1u);
		BOOST_CHECK_EQUAL(primeSet.count(3), 1u);
		BOOST_CHECK_EQUAL(primeSet.count(5), 1u);
		BOOST_CHECK_EQUAL(primeSet.count(7), 1u);
		BOOST_CHECK_EQUAL(primeSet.count(11), 1u);
	}

	BOOST_AUTO_TEST_CASE(testZero)
	{
		std::set<int> primeSet = GeneratePrimeNumbersSet(0);
		BOOST_CHECK_EQUAL(primeSet.size(), 0u);
	}

	BOOST_AUTO_TEST_CASE(testNegative)
	{
		std::set<int> primeSet = GeneratePrimeNumbersSet(-11);
		BOOST_CHECK_EQUAL(primeSet.size(), 0u);
	}

	BOOST_AUTO_TEST_CASE(testLarge)
	{
		std::set<int> primeSet = GeneratePrimeNumbersSet(100000000);
		BOOST_CHECK_EQUAL(primeSet.size(), 5761455u);
	}

	BOOST_AUTO_TEST_CASE(testTooLargeError)
	{
		BOOST_CHECK_THROW(GeneratePrimeNumbersSet(100000001), std::invalid_argument);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testToString)
	BOOST_AUTO_TEST_CASE(testNormal)
	{
		std::set<int> primeSet = GeneratePrimeNumbersSet(11);
		string primeSetString = IntSetToString(primeSet);
		string expected = "2 3 5 7 11";

		BOOST_CHECK_EQUAL(primeSetString, expected);
	}

	BOOST_AUTO_TEST_CASE(testEmpty)
	{
		std::set<int> primeSet = GeneratePrimeNumbersSet(0);
		string primeSetString = IntSetToString(primeSet);
		string expected = "";

		BOOST_CHECK_EQUAL(primeSetString, expected);
	}
BOOST_AUTO_TEST_SUITE_END()
