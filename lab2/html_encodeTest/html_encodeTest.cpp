#include "pch.h"
#include "../html_encode/html_logic.h"
#include "../html_encode/html_logic.cpp"
#define BOOST_TEST_MODULE html_encodeTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(testHtmlEncode)

BOOST_AUTO_TEST_CASE(testEncode) {
	BOOST_CHECK(HtmlEncode(" as  d ") == " as  d ");
	BOOST_CHECK(HtmlEncode("<>\"'&") == "&lt;&gt;&quot;&apos;&amp;");
	BOOST_CHECK(HtmlEncode("") == "");
}

BOOST_AUTO_TEST_SUITE_END()
