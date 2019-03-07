#include "pch.h"
#include "../crypt/SwapEncryptor.h"

#define BOOST_TEST_MODULE CryptTest
#include <boost/test/unit_test.hpp>

struct EncryptorFixture
{
	uint8_t key = 0b10101010;
};

BOOST_FIXTURE_TEST_SUITE(testCrypt, EncryptorFixture)

	BOOST_AUTO_TEST_SUITE(testSwapBits)
		BOOST_AUTO_TEST_CASE(testSwap)
		{
			BOOST_CHECK_EQUAL(swapBits(0b00000001), 0b00000100);
			BOOST_CHECK_EQUAL(swapBits(0b00000010), 0b00001000);
			BOOST_CHECK_EQUAL(swapBits(0b00000100), 0b00010000);
			BOOST_CHECK_EQUAL(swapBits(0b00001000), 0b01000000);
			BOOST_CHECK_EQUAL(swapBits(0b00010000), 0b10000000);
			BOOST_CHECK_EQUAL(swapBits(0b00100000), 0b00000001);
			BOOST_CHECK_EQUAL(swapBits(0b01000000), 0b00000010);
			BOOST_CHECK_EQUAL(swapBits(0b10000000), 0b00100000);
		}

		BOOST_AUTO_TEST_CASE(testSwapBack)
		{
			BOOST_CHECK_EQUAL(swapBitsBack(0b00000001), 0b00100000);
			BOOST_CHECK_EQUAL(swapBitsBack(0b00000010), 0b01000000);
			BOOST_CHECK_EQUAL(swapBitsBack(0b00000100), 0b00000001);
			BOOST_CHECK_EQUAL(swapBitsBack(0b00001000), 0b00000010);
			BOOST_CHECK_EQUAL(swapBitsBack(0b00010000), 0b00000100);
			BOOST_CHECK_EQUAL(swapBitsBack(0b00100000), 0b10000000);
			BOOST_CHECK_EQUAL(swapBitsBack(0b01000000), 0b00001000);
			BOOST_CHECK_EQUAL(swapBitsBack(0b10000000), 0b00010000);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testEncodeByte)
		BOOST_AUTO_TEST_CASE(testEncode)
		{
			BOOST_CHECK_EQUAL(encodeByte(0b00001111, key), 0b00110101);
			BOOST_CHECK_EQUAL(encodeByte(0b11110000, key), 0b11001010);
		}

		BOOST_AUTO_TEST_CASE(testDecode)
		{
			BOOST_CHECK_EQUAL(decodeByte(0b00110101, key), 0b00001111);
			BOOST_CHECK_EQUAL(decodeByte(0b11001010, key), 0b11110000);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testEncodeStream)
		BOOST_AUTO_TEST_CASE(testEncodeStream)
		{
			std::stringstream inputSs;
			std::stringstream outputSs;

			std::string text = "HelloWorld!";
			inputSs << text;

			encryptStream("crypt", inputSs, outputSs, key);
			inputSs.str(std::string());
			inputSs.clear();
			BOOST_CHECK(outputSs.str() != text);

			encryptStream("decrypt", outputSs, inputSs, key);
			BOOST_CHECK_EQUAL(inputSs.str(), text);
		}

		BOOST_AUTO_TEST_CASE(testEncodeStreamSpaces)
		{
			std::stringstream inputSs;
			std::stringstream outputSs;

			std::string text = "Hello  World !";
			inputSs << text;

			encryptStream("crypt", inputSs, outputSs, key);
			inputSs.str(std::string());
			inputSs.clear();
			BOOST_CHECK(outputSs.str() != text);

			encryptStream("decrypt", outputSs, inputSs, key);
			BOOST_CHECK_EQUAL(inputSs.str(), text);
		}

		BOOST_AUTO_TEST_CASE(testEncodeStreamEndline)
		{
			std::stringstream inputSs;
			std::stringstream outputSs;

			std::string text = "Hello\nWorld!";
			inputSs << text;

			encryptStream("crypt", inputSs, outputSs, key);
			inputSs.str(std::string());
			inputSs.clear();
			BOOST_CHECK(outputSs.str() != text);

			encryptStream("decrypt", outputSs, inputSs, key);
			BOOST_CHECK_EQUAL(inputSs.str(), text);
		}

		BOOST_AUTO_TEST_CASE(testEncodeErrInvalidMode)
		{
			std::string text = "Hello\nWorld!";
			std::stringstream ss;
			ss << text;
			std::stringstream outputSs;
			BOOST_CHECK_THROW(encryptStream("encode", ss, outputSs, key), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
