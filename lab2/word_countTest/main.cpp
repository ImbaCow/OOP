#include "pch.h"
#include "../word_count/WordsMap.h"

#define BOOST_TEST_MODULE WordsMapTest
#include <boost/test/unit_test.hpp>

using namespace std;

struct WordsMapFixture
{
	map<string, size_t> wordsMap;
};

BOOST_FIXTURE_TEST_SUITE(testMap, WordsMapFixture)

	BOOST_AUTO_TEST_SUITE(testAdding)
		BOOST_AUTO_TEST_CASE(testSingle)
		{
			stringstream ss("Hello");

			wordsMap = CreateWordsMap(ss);
			BOOST_CHECK_EQUAL(wordsMap.count("hello"), 1);
			BOOST_CHECK_EQUAL(wordsMap.size(), 1);
		}
		BOOST_AUTO_TEST_CASE(testList)
		{
			stringstream ss("Hello Open World !");

			wordsMap = CreateWordsMap(ss);
			BOOST_CHECK_EQUAL(wordsMap.count("hello"), 1);
			BOOST_CHECK_EQUAL(wordsMap.count("open"), 1);
			BOOST_CHECK_EQUAL(wordsMap.count("world"), 1);
			BOOST_CHECK_EQUAL(wordsMap.count("!"), 1);
			BOOST_CHECK_EQUAL(wordsMap.size(), 4);
		}
		BOOST_AUTO_TEST_CASE(testEmpty)
		{
			stringstream ss("");

			wordsMap = CreateWordsMap(ss);
			BOOST_CHECK_EQUAL(wordsMap.size(), 0);
		}
		BOOST_AUTO_TEST_CASE(testDuplicate)
		{
			stringstream ss("Hello hELLO World HELLO WORLD HeLlO !");

			wordsMap = CreateWordsMap(ss);
			BOOST_CHECK_EQUAL(wordsMap.size(), 3);
			BOOST_CHECK_EQUAL(wordsMap["hello"], 4);
			BOOST_CHECK_EQUAL(wordsMap["world"], 2);
			BOOST_CHECK_EQUAL(wordsMap["!"], 1);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testToString)
		BOOST_AUTO_TEST_CASE(testSingle)
		{
			stringstream ss("Hello");

			string wordsMapStr = WordsMapToString(CreateWordsMap(ss));
			BOOST_CHECK_EQUAL(wordsMapStr, "hello - 1\n");
		}
		BOOST_AUTO_TEST_CASE(testWordsList)
		{
			stringstream ss("Hello World !");

			string wordsMapStr = WordsMapToString(CreateWordsMap(ss));
			BOOST_CHECK_EQUAL(wordsMapStr, "! - 1\nhello - 1\nworld - 1\n"); 
		}
		BOOST_AUTO_TEST_CASE(testDuplicate)
		{
			stringstream ss("Hello hELLO World HELLO WORLD HeLlO");

			string wordsMapStr = WordsMapToString(CreateWordsMap(ss));
			BOOST_CHECK_EQUAL(wordsMapStr, "hello - 4\nworld - 2\n");
		}
		BOOST_AUTO_TEST_CASE(testEmpty)
		{
			stringstream ss("");

			string wordsMapStr = WordsMapToString(CreateWordsMap(ss));
			BOOST_CHECK_EQUAL(wordsMapStr, "");
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
