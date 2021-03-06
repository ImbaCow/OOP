#include "pch.h"
#include "../lab7/FindUtils.h"
#include "../lab7/Human.h"

#define BOOST_TEST_MODULE FindMaxTest
#include "boost/test/unit_test.hpp"

using namespace std;

struct FindMaxHumanTestFixture
{
};

BOOST_FIXTURE_TEST_SUITE(testFindMax, FindMaxHumanTestFixture)
	BOOST_AUTO_TEST_CASE(testFindMaxHumanWeight)
	{
		std::vector<Human> humanArr = {
			{ "common human name", 160, 60 },
			{ "common2 human2 name2", 180, 70 },
			{ "common3 human3 name3", 170, 80 }
		};

		Human maxHuman;
		BOOST_REQUIRE(FindMax(humanArr, maxHuman, Human::lessHumanWeight));
		BOOST_CHECK_EQUAL(maxHuman, Human({ "common3 human3 name3", 170u, 80u }));
	}
	BOOST_AUTO_TEST_CASE(testFindMaxHumanHeight)
	{
		std::vector<Human> humanArr = {
			{ "common human name", 160, 60 },
			{ "common2 human2 name2", 180, 70 },
			{ "common3 human3 name3", 170, 80 }
		};

		Human maxHuman;
		BOOST_REQUIRE(FindMax(humanArr, maxHuman, Human::lessHumanHeight));
		BOOST_CHECK_EQUAL(maxHuman, Human({ "common2 human2 name2", 180u, 70u }));
	}
	BOOST_AUTO_TEST_CASE(testFindEmpty)
	{
		std::vector<Human> humanArr;

		Human maxHuman{ "common2 human2 name2", 180u, 70u };
		BOOST_REQUIRE(!FindMax(humanArr, maxHuman, Human::lessHumanHeight));
		BOOST_CHECK_EQUAL(maxHuman, Human({ "common2 human2 name2", 180u, 70u }));
	}
	BOOST_AUTO_TEST_CASE(testCharPtr)
	{
		const char* charPtr = "3";
		std::vector<const char*> ptrArr{ "1", "2", charPtr };

		const char* maxPtr;
		BOOST_REQUIRE(FindMax(ptrArr, maxPtr));
		BOOST_CHECK_EQUAL(maxPtr, "3");
	}
BOOST_AUTO_TEST_SUITE_END()