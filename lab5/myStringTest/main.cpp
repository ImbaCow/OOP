#pragma once
#include "pch.h"
#include "../myString/CMyString.h"

#define BOOST_TEST_MODULE MyStringTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(testContructors)
	BOOST_AUTO_TEST_CASE(testEmpty)
	{
		CMyString str;
		BOOST_CHECK_EQUAL(str.GetLength(), 0u);
		BOOST_CHECK_EQUAL(string(str.GetStringData()), string(""));
	}
	BOOST_AUTO_TEST_CASE(testCharArr)
	{
		CMyString str1("hello world");
		CMyString str2("hell\0 world");

		BOOST_CHECK_EQUAL(str1.GetLength(), 11u);
		BOOST_CHECK_EQUAL(str2.GetLength(), 4u);

		BOOST_CHECK_EQUAL(string(str1.GetStringData()), string("hello world"));
		BOOST_CHECK_EQUAL(string(str2.GetStringData()), string("hell"));
	}
	BOOST_AUTO_TEST_CASE(testCharArrWithLength)
	{
		CMyString str1("hello world", 5);
		CMyString str2("he\0llo world", 5);

		BOOST_CHECK_EQUAL(str1.GetLength(), 5u);
		BOOST_CHECK_EQUAL(str2.GetLength(), 5u);

		BOOST_CHECK_EQUAL(string(str1.GetStringData(), 5), string("hello", 5));
		BOOST_CHECK_EQUAL(string(str2.GetStringData(), 5), string("he\0ll", 5));
	}
	BOOST_AUTO_TEST_CASE(testCopy)
	{
		CMyString str1("hello world");
		CMyString str2(str1);
		BOOST_CHECK_EQUAL(str2.GetLength(), str1.GetLength());
		BOOST_CHECK_EQUAL(string(str2.GetStringData()), string(str1.GetStringData()));
	}
	BOOST_AUTO_TEST_CASE(testMove)
	{
		CMyString str(CMyString("hello world"));
		BOOST_CHECK_EQUAL(str.GetLength(), 11u);
		BOOST_CHECK_EQUAL(string(str.GetStringData()), string("hello world"));
	}
	BOOST_AUTO_TEST_CASE(testAfterMove)
	{
		CMyString str1("hello world");
		CMyString str2 = std::move(str1);
		BOOST_CHECK_EQUAL(str1.GetLength(), 0u);
		BOOST_CHECK_EQUAL(str1.GetStringData(), nullptr);
	}
	BOOST_AUTO_TEST_CASE(testStdString)
	{
		string str1("hello world");
		string str2("hell\0 world", 11);

		CMyString str11(str1);
		CMyString str22(str2);

		BOOST_CHECK_EQUAL(str11.GetLength(), 11u);
		BOOST_CHECK_EQUAL(str22.GetLength(), 11u);

		BOOST_CHECK_EQUAL(string(str11.GetStringData(), str11.GetLength()), str1);
		BOOST_CHECK_EQUAL(string(str22.GetStringData(), str22.GetLength()), str2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testFunc)

	BOOST_AUTO_TEST_SUITE(testClear)
		BOOST_AUTO_TEST_CASE(testClearSize)
		{
			CMyString str("hello world");
			str.Clear();
			BOOST_CHECK_EQUAL(str.GetLength(), 0u);
			BOOST_CHECK_EQUAL(string(str.GetStringData()), string());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testSubstr)
		BOOST_AUTO_TEST_CASE(testSubstrBase)
		{
			CMyString str("hello world");
			CMyString substr = str.SubString(0, 4);
			BOOST_CHECK_EQUAL(substr.GetLength(), 4u);
			BOOST_CHECK_EQUAL(string(substr.GetStringData()), string("hell"));
		}
		BOOST_AUTO_TEST_CASE(testSubstrOverLength)
		{
			CMyString str("hello world");
			CMyString substr = str.SubString(2, 100);
			BOOST_CHECK_EQUAL(substr.GetLength(), 9u);
			BOOST_CHECK_EQUAL(string(substr.GetStringData()), string("llo world"));
		}
		BOOST_AUTO_TEST_CASE(testSubstrWithoutLength)
		{
			CMyString str("hello world");
			CMyString substr = str.SubString(3);
			BOOST_CHECK_EQUAL(substr.GetLength(), 8u);
			BOOST_CHECK_EQUAL(string(substr.GetStringData()), string("lo world"));
		}
		BOOST_AUTO_TEST_CASE(testSubstrOverLengthOffset)
		{
			CMyString str("hello");
			BOOST_CHECK_THROW(str.SubString(10), exception);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testOperators)

	BOOST_AUTO_TEST_SUITE(testAssign)
		BOOST_AUTO_TEST_CASE(testBase)
		{
			CMyString str1;
			CMyString str2("hello world");
			str1 = str2;
			BOOST_CHECK_EQUAL(str1.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str1.GetStringData()), string("hello world"));
		}
		BOOST_AUTO_TEST_CASE(testSelf)
		{
			CMyString str("hello world");
			str = str;
			BOOST_CHECK_EQUAL(str.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str.GetStringData()), string("hello world"));
		}
		BOOST_AUTO_TEST_CASE(testCharArr)
		{
			CMyString str1;
			str1 = "hello world";
			BOOST_CHECK_EQUAL(str1.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str1.GetStringData()), string("hello world"));
		}
		BOOST_AUTO_TEST_CASE(testStdString)
		{
			CMyString str1;
			str1 = string("hello world");
			BOOST_CHECK_EQUAL(str1.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str1.GetStringData()), string("hello world"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testBrackets)
		BOOST_AUTO_TEST_CASE(testGetValue)
		{
			CMyString str1("hello world");
			CMyString str2;

			BOOST_CHECK_EQUAL(str1[4], 'o');
		}
		BOOST_AUTO_TEST_CASE(testSetValue)
		{
			CMyString str("hello world");
			str[4] = '0';

			BOOST_CHECK_EQUAL(string(str.GetStringData()), string("hell0 world"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testConcat)
		BOOST_AUTO_TEST_CASE(testBase)
		{
			CMyString str1("hello");
			CMyString str2(" ");
			CMyString str3("world");

			CMyString str = str1 + str2 + str3;
			BOOST_CHECK_EQUAL(str.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str.GetStringData()), string("hello world"));
		}
		BOOST_AUTO_TEST_CASE(testAnotherTypes)
		{
			const char* str1 = "hello";
			string str2(" ");
			CMyString str3("world");

			CMyString str23 = str2 + str3;
			CMyString str = str1 + str23;
			BOOST_CHECK_EQUAL(str.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str.GetStringData()), string("hello world"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testSelfConcat)
		BOOST_AUTO_TEST_CASE(testBase)
		{
			CMyString str1("hello");
			CMyString str2(" world");

			str1 += str2;
			BOOST_CHECK_EQUAL(str1.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str1.GetStringData()), string("hello world"));
		}
		BOOST_AUTO_TEST_CASE(testAnotherTypes)
		{
			CMyString str1 = "hello";
			const char* str2(" ");
			string str3("world");

			str1 += str2;
			str1 += str3;
			BOOST_CHECK_EQUAL(str1.GetLength(), 11u);
			BOOST_CHECK_EQUAL(string(str1.GetStringData()), string("hello world"));
		}
		BOOST_AUTO_TEST_CASE(testSelf)
		{
			CMyString str1 = "hello";

			str1 += str1 += str1;
			BOOST_CHECK_EQUAL(str1.GetLength(), 20u);
			BOOST_CHECK_EQUAL(string(str1.GetStringData()), string("hellohellohellohello"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testCompare)

		BOOST_AUTO_TEST_SUITE(testEqual)
			BOOST_AUTO_TEST_CASE(testBase)
			{
				CMyString str1("hell\0o");
				CMyString str2("hello", 4);
				CMyString str3("hellO");

				BOOST_CHECK(str1 == str2);
				BOOST_CHECK(!(str1 == str3));
			}
			BOOST_AUTO_TEST_CASE(testAnotherTypes)
			{
				CMyString str1("hello");
				const char* str2 = "hello";
				string str3("hello");

				BOOST_CHECK(str2 == str1);
				BOOST_CHECK(str3 == str1);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testNotEqual)
			BOOST_AUTO_TEST_CASE(testBase)
			{
				CMyString str1("hell\0", 5);
				CMyString str2("hello");
				CMyString str3("hell\0", 5);

				BOOST_CHECK(str1 != str2);
				BOOST_CHECK(!(str1 != str3));
			}
			BOOST_AUTO_TEST_CASE(testCharArrWithZeroEnd)
			{
				string stdStr(CMyString("hell\0", 5).GetStringData(), 5);
				string notExpectedStr("hell");

				BOOST_CHECK_PREDICATE(std::not_equal_to<CMyString>(), (notExpectedStr)(stdStr));
			}
			BOOST_AUTO_TEST_CASE(testAnotherTypes)
			{
				CMyString str1("hell\0", 5);
				const char* str2 = "hello";
				string str3("hell");

				BOOST_CHECK(str2 != str1);
				BOOST_CHECK(str3 != str1);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testCompare)
			BOOST_AUTO_TEST_CASE(testGreater)
			{
				CMyString str1("hello");
				CMyString str2("hellO");
				CMyString str3("helloO");

				BOOST_CHECK(str1 > str2);
				BOOST_CHECK(!(str2 > str1));
			}
			BOOST_AUTO_TEST_CASE(testGreaterAnotherType)
			{
				CMyString str1("hellO");
				string str2("hello");
				const char* str3 = "hello";

				BOOST_CHECK(str2 > str1);
				BOOST_CHECK(str3 > str1);
			}
			BOOST_AUTO_TEST_CASE(testLess)
			{
				CMyString str1("hello");
				CMyString str2("hellO");
				CMyString str3("helloO");

				BOOST_CHECK(str2 < str1);
				BOOST_CHECK(str1 < str3);
				BOOST_CHECK(!(str3 < str1));
			}
			BOOST_AUTO_TEST_CASE(testLexMore)
			{
				CMyString str1("ab");
				CMyString str2("b");

				BOOST_CHECK(str2 > str1);
			}
			BOOST_AUTO_TEST_CASE(testLessAnotherType)
			{
				CMyString str1("hello");
				string str2("hellO");
				const char* str3 = "hellO";

				BOOST_CHECK(str2 < str1);
				BOOST_CHECK(str3 < str1);
			}
			BOOST_AUTO_TEST_CASE(testGreaterEqual)
			{
				CMyString str1("hello");
				CMyString str2("hellO");
				CMyString str3("hello");

				BOOST_CHECK(str1 >= str2);
				BOOST_CHECK(str1 >= str3);
				BOOST_CHECK(!(str2 >= str1));
			}
			BOOST_AUTO_TEST_CASE(testGreaterEqualAnotherType)
			{
				CMyString str1("hellO");
				string str2("hello");
				const char* str3 = "hellO";

				BOOST_CHECK(str2 >= str1);
				BOOST_CHECK(str3 >= str1);
			}
			BOOST_AUTO_TEST_CASE(testLessEqual)
			{
				CMyString str1("hellO");
				CMyString str2("hello");
				CMyString str3("hellO");

				BOOST_CHECK(str1 <= str2);
				BOOST_CHECK(str1 <= str3);
				BOOST_CHECK(!(str2 <= str1));
			}
			BOOST_AUTO_TEST_CASE(testLessEqualAnotherType)
			{
				CMyString str1("hello");
				string str2("hellO");
				const char* str3 = "hello";

				BOOST_CHECK(str2 <= str1);
				BOOST_CHECK(str3 <= str1);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testStream)
		BOOST_AUTO_TEST_CASE(testOStream)
		{
			CMyString str("hell\0 world", 11);
			stringstream ss("");
			ss << str;
			BOOST_CHECK_EQUAL(ss.str(), std::string("hell\0 world", 11));
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

struct IteratorFixture
{
	CMyString str = "hello world";
	const CMyString cstr = "hello world";
};

BOOST_FIXTURE_TEST_SUITE(testIterators, IteratorFixture)

	BOOST_AUTO_TEST_SUITE(testIter)
		BOOST_AUTO_TEST_CASE(testBegin)
		{
			auto it = str.begin();
			BOOST_CHECK_EQUAL(*it, 'h');
		}
		BOOST_AUTO_TEST_CASE(testEnd)
		{
			auto it = str.end();
			BOOST_CHECK_EQUAL(*it, '\0');
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testConstIter)
		BOOST_AUTO_TEST_CASE(testBegin)
		{
			auto cit = cstr.begin();
			BOOST_CHECK_EQUAL(*cit, 'h');
		}
		BOOST_AUTO_TEST_CASE(testEnd)
		{
			auto cit = cstr.end();
			BOOST_CHECK_EQUAL(*cit, '\0');
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testReverseIter)
		BOOST_AUTO_TEST_CASE(testRBegin)
		{
			auto it = str.rbegin();
			BOOST_CHECK_EQUAL(*it, 'd');
		}
		BOOST_AUTO_TEST_CASE(testREnd)
		{
			auto it = str.rend();
			BOOST_CHECK_EQUAL(*(it - 1), 'h');
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testIterOperators)

		BOOST_AUTO_TEST_SUITE(testIterPlus)
			BOOST_AUTO_TEST_CASE(testIterIncrement)
			{
				auto it = str.begin();
				++it;
				BOOST_CHECK_EQUAL(*it, 'e');
			}
			BOOST_AUTO_TEST_CASE(testIterPlusInt)
			{
				auto it = str.begin();
				it += 2;
				BOOST_CHECK_EQUAL(*(it + 2), 'o');
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testIterMinus)
			BOOST_AUTO_TEST_CASE(testIterDecrement)
			{
				auto it = str.end();
				--it;
				BOOST_CHECK_EQUAL(*it, 'd');
			}
			BOOST_AUTO_TEST_CASE(testIterMinusInt)
			{
				auto it = str.end();
				it -= 2;
				BOOST_CHECK_EQUAL(*(it - 2), 'o');
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testIterBrackets)
			BOOST_AUTO_TEST_CASE(testIterGet)
			{
				auto it = str.begin();
				BOOST_CHECK_EQUAL((it + 1)[1], 'l');
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testIterCompare)
			BOOST_AUTO_TEST_CASE(testIterEqual)
			{
				auto it1 = str.begin();
				auto it2 = str.begin();
				auto it3 = str.end();

				BOOST_CHECK(it1 == it2);
				BOOST_CHECK(!(it1 == it3));
			}
			BOOST_AUTO_TEST_CASE(testIterNotEqual)
			{
				auto it1 = str.begin();
				auto it2 = str.begin();
				auto it3 = str.end();

				BOOST_CHECK(it1 != it3);
				BOOST_CHECK(!(it1 != it2));
			}
			BOOST_AUTO_TEST_CASE(testIterGreater)
			{
				auto it1 = str.begin();
				auto it2 = str.end();

				BOOST_CHECK(it2 > it1);
				BOOST_CHECK(!(it1 > it2));
			}
			BOOST_AUTO_TEST_CASE(testIterGreaterEqual)
			{
				auto it1 = str.begin();
				auto it2 = str.end();
				auto it3 = str.end();

				BOOST_CHECK(it2 >= it1);
				BOOST_CHECK(it2 >= it3);
				BOOST_CHECK(!(it1 >= it2));
			}
			BOOST_AUTO_TEST_CASE(testIterLess)
			{
				auto it1 = str.begin();
				auto it2 = str.end();

				BOOST_CHECK(it1 < it2);
				BOOST_CHECK(!(it2 < it1));
			}
			BOOST_AUTO_TEST_CASE(testIterLessEqual)
			{
				auto it1 = str.begin();
				auto it2 = str.end();
				auto it3 = str.end();

				BOOST_CHECK(it1 <= it2);
				BOOST_CHECK(it2 <= it3);
				BOOST_CHECK(!(it2 <= it1));
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testIterFor)
		BOOST_AUTO_TEST_CASE(testForLoop)
		{
			string strCopy;
			for (auto ch : str)
			{
				strCopy += ch;
			}

			BOOST_CHECK_EQUAL(strCopy, string(str.GetStringData()));
		}
		BOOST_AUTO_TEST_CASE(testForLoopFull)
		{
			string strCopy;
			for (auto it = str.begin(); it != str.end(); ++it)
			{
				strCopy += *it;
			}

			BOOST_CHECK_EQUAL(strCopy, string(str.GetStringData()));
		}
		BOOST_AUTO_TEST_CASE(testReverseForLoopFull)
		{
			string strCopy;
			for (auto it = str.rbegin(); it != str.rend(); ++it)
			{
				strCopy += *it;
			}

			BOOST_CHECK_EQUAL(strCopy, string("dlrow olleh"));
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
