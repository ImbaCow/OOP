#include <cstdint>
#include <string>
#include "../flipbyte/logic.cpp"
#define BOOST_TEST_MODULE TvTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(flipByteTests);

BOOST_AUTO_TEST_CASE(getInputByteTest) {
	BOOST_CHECK_THROW(GetInputByte("One"), exception);
	BOOST_CHECK_THROW(GetInputByte("2566"), invalid_argument);
	BOOST_CHECK(GetInputByte("255") == 255);
}

BOOST_AUTO_TEST_CASE(getIFlipedByteTest) {
	BOOST_CHECK(GetFlipedByte(6) == 96);
	BOOST_CHECK(GetFlipedByte(96) == 6);
	BOOST_CHECK(GetFlipedByte(0) == 255);
	BOOST_CHECK(GetFlipedByte(255) == 0);
	BOOST_CHECK(GetFlipedByte(128) == 1);
}

BOOST_AUTO_TEST_SUITE_END();
