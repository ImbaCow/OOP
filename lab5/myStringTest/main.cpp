#include "pch.h"
#include "../myString/CMyString.h"

#define BOOST_TEST_MODULE MyStringTest
#include <boost/test/unit_test.hpp>

using namespace std;

struct TestContext
{
	bool IsCharArrEqual(const char* first, const char* second)
	{
		size_t aLen = strlen(first);
		size_t bLen = strlen(second);
		
		return memcmp(first, second, std::min(aLen, bLen)) == 0;
	}
};

BOOST_FIXTURE_TEST_SUITE(testBase, TestContext)

	BOOST_AUTO_TEST_SUITE(testContructors)
		BOOST_AUTO_TEST_CASE(testEmpty)
		{
			CMyString str;
			BOOST_CHECK_EQUAL(str.GetLength(), 0);
			BOOST_CHECK(IsCharArrEqual(str.GetStringData(), ""));
		}
		BOOST_AUTO_TEST_CASE(testCharArr)
		{
			CMyString str("hello world");
			BOOST_CHECK_EQUAL(str.GetLength(), 11);
			BOOST_CHECK(IsCharArrEqual(str.GetStringData(), "hello world"));
		}
		BOOST_AUTO_TEST_CASE(testCharArrWithLength)
		{
			CMyString str("he\0llo world", 4);
			BOOST_CHECK_EQUAL(str.GetLength(), 4);
			BOOST_CHECK(IsCharArrEqual(str.GetStringData(), "he\0l"));
		}
		BOOST_AUTO_TEST_CASE(testCopy)
		{
			CMyString str1("hello world");
			CMyString str2(str1);
			BOOST_CHECK_EQUAL(str2.GetLength(), str1.GetLength());
			BOOST_CHECK(IsCharArrEqual(str2.GetStringData(), str1.GetStringData()));
		}
		BOOST_AUTO_TEST_CASE(testMove)
		{
			CMyString str2(CMyString("hello world"));
			BOOST_CHECK_EQUAL(str2.GetLength(), 11);
			BOOST_CHECK(IsCharArrEqual(str2.GetStringData(), "hello world"));
		}
		BOOST_AUTO_TEST_CASE(testStdString)
		{
			string str1 = "hello world";
			CMyString str2(str1);
			BOOST_CHECK_EQUAL(str2.GetLength(), 11);
			BOOST_CHECK(IsCharArrEqual(str2.GetStringData(), "hello world"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testFunc)

		/*BOOST_AUTO_TEST_SUITE(testClear)
			BOOST_AUTO_TEST_CASE(testClearSize)
			{
				CMyString str("hello world");
				str.Clear();
				BOOST_CHECK_EQUAL(str.GetLength(), 0);
				BOOST_CHECK(IsCharArrEqual(str.GetStringData(), ""));
			}
		BOOST_AUTO_TEST_SUITE_END()*/

		BOOST_AUTO_TEST_SUITE(testSubstr)
			BOOST_AUTO_TEST_CASE(testSubstrBase)
			{
				CMyString str("hello world");
				CMyString substr = str.SubString(0, 4);
				BOOST_CHECK_EQUAL(substr.GetLength(), 4);
				BOOST_CHECK(IsCharArrEqual(substr.GetStringData(), "hell"));
			}
			BOOST_AUTO_TEST_CASE(testSubstrOverLength)
			{
				CMyString str("hello world");
				CMyString substr = str.SubString(2, 10);
				BOOST_CHECK_EQUAL(substr.GetLength(), 9);
				BOOST_CHECK(IsCharArrEqual(substr.GetStringData(), "llo world"));
			}
			BOOST_AUTO_TEST_CASE(testSubstrWrongParams)
			{
				CMyString str("hello");
				BOOST_CHECK_THROW(str.SubString(10), exception);
			}
			BOOST_AUTO_TEST_CASE(testSubstrWithoutLength)
			{
				CMyString str("hello world");
				CMyString substr = str.SubString(3);
				BOOST_CHECK_EQUAL(substr.GetLength(), 8);
				BOOST_CHECK(IsCharArrEqual(substr.GetStringData(), "lo world"));
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
				BOOST_CHECK_EQUAL(str1.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str1.GetStringData(), "hello world"));
			}
			BOOST_AUTO_TEST_CASE(testSelf)
			{
				CMyString str("hello world");
				str = str;
				BOOST_CHECK_EQUAL(str.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str.GetStringData(), "hello world"));
			}
			BOOST_AUTO_TEST_CASE(testCharArr)
			{
				CMyString str1;
				str1 = "hello world";
				BOOST_CHECK_EQUAL(str1.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str1.GetStringData(), "hello world"));
			}
			BOOST_AUTO_TEST_CASE(testStdString)
			{
				CMyString str1;
				str1 = string("hello world");
				BOOST_CHECK_EQUAL(str1.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str1.GetStringData(), "hello world"));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testConcat)
			BOOST_AUTO_TEST_CASE(testBase)
			{
				CMyString str1("hello");
				CMyString str2(" ");
				CMyString str3("world");

				CMyString str = str1 + str2 + str3;
				BOOST_CHECK_EQUAL(str.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str.GetStringData(), "hello world"));
			}
			BOOST_AUTO_TEST_CASE(testAnotherTypes)
			{
				const char* str1 = "hello";
				string str2(" ");
				CMyString str3("world");

				CMyString str23 = str2 + str3;
				CMyString str = str1 + str23;
				BOOST_CHECK_EQUAL(str.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str.GetStringData(), "hello world"));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testSelfConcat)
			BOOST_AUTO_TEST_CASE(testBase)
			{
				CMyString str1("hello");
				CMyString str2(" world");

				str1 += str2;
				BOOST_CHECK_EQUAL(str1.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str1.GetStringData(), "hello world"));
			}
			BOOST_AUTO_TEST_CASE(testAnotherTypes)
			{
				CMyString str1 = "hello";
				const char* str2(" ");
				string str3("world");

				str1 += str2;
				str1 += str3;
				BOOST_CHECK_EQUAL(str1.GetLength(), 11);
				BOOST_CHECK(IsCharArrEqual(str1.GetStringData(), "hello world"));
			}
			BOOST_AUTO_TEST_CASE(testSelf)
			{
				CMyString str1 = "hello";

				str1 += str1 += str1;
				BOOST_CHECK_EQUAL(str1.GetLength(), 20);
				BOOST_CHECK(IsCharArrEqual(str1.GetStringData(), "hellohellohellohello"));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(testCompare)

			BOOST_AUTO_TEST_SUITE(testEqual)
				BOOST_AUTO_TEST_CASE(testBase)
				{
					CMyString str1("helloo");
					CMyString str2("helloo");
					CMyString str3("hello");

					BOOST_CHECK(str1 == str2);
					BOOST_CHECK(!(str1 == str3));
				}
				BOOST_AUTO_TEST_CASE(testAnotherTypes)
				{
					CMyString str1("helloo");
					const char* str2 = "helloo";
					string str3("hello");

					BOOST_CHECK(str2 == str1);
					BOOST_CHECK(!(str3 == str1));
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testNotEqual)
				BOOST_AUTO_TEST_CASE(testBase)
				{
					CMyString str1("helloo");
					CMyString str2("helloo");
					CMyString str3("hello");

					BOOST_CHECK(!(str1 != str2));
					BOOST_CHECK(str1 != str3);
				}
				BOOST_AUTO_TEST_CASE(testAnotherTypes)
				{
					CMyString str1("helloo");
					const char* str2 = "helloo";
					string str3("hello");

					BOOST_CHECK(!(str2 != str1));
					BOOST_CHECK(str3 != str1);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testCompare)
				BOOST_AUTO_TEST_CASE(testGreater)
				{
					CMyString str1("hello");
					CMyString str2("hellO");

					BOOST_CHECK(str1 > str2);
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
					CMyString str1("hellO");
					CMyString str2("hello");

					BOOST_CHECK(str1 < str2);
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
				CMyString str("hello world");
				stringstream ss("");
				ss << str;
				BOOST_CHECK_EQUAL(ss.str(), "hello world");
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()