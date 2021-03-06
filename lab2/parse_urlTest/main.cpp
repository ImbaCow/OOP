#include "pch.h"
#include "../parse_url/URL.h"

#define BOOST_TEST_MODULE ParseUrlTest
#include <boost/test/unit_test.hpp>

using namespace std;

struct URLParamsFixture
{
	Protocol protocol;
	string host;
	int port;
	string document;
};

BOOST_FIXTURE_TEST_SUITE(testParse, URLParamsFixture)
	BOOST_AUTO_TEST_CASE(testFullUrl)
	{
		string url = "https://example.com:8000/doc/as";

		BOOST_CHECK(ParseURL(url, protocol, port, host, document));
		BOOST_CHECK_EQUAL(protocol, Protocol::HTTPS);
		BOOST_CHECK_EQUAL(host, "example.com");
		BOOST_CHECK_EQUAL(port, 8000);
		BOOST_CHECK_EQUAL(document, "doc/as");
	}
	BOOST_AUTO_TEST_CASE(testDefaultProtocol)
	{
		string url = "example.com:8000/doc/as";

		BOOST_CHECK(ParseURL(url, protocol, port, host, document));
		BOOST_CHECK_EQUAL(protocol, Protocol::HTTP);
	}
	BOOST_AUTO_TEST_CASE(testWithoutDocument)
	{
		string url = "https://example.com:8000";

		BOOST_CHECK(ParseURL(url, protocol, port, host, document));
		BOOST_CHECK_EQUAL(protocol, Protocol::HTTPS);
		BOOST_CHECK_EQUAL(host, "example.com");
		BOOST_CHECK_EQUAL(port, 8000);
		BOOST_CHECK_EQUAL(document, "");
	}

	BOOST_AUTO_TEST_SUITE(testPorts)
		BOOST_AUTO_TEST_CASE(testHttpPort)
		{
			string url = "http://example.com";
			BOOST_CHECK(ParseURL(url, protocol, port, host, document));
			BOOST_CHECK_EQUAL(port, 80);
		}
		BOOST_AUTO_TEST_CASE(testDefaultHttpPort)
		{
			string url = "example.com";
			BOOST_CHECK(ParseURL(url, protocol, port, host, document));
			BOOST_CHECK_EQUAL(port, 80);
		}
		BOOST_AUTO_TEST_CASE(testHttpsPort)
		{
			string url = "https://example.com";
			BOOST_CHECK(ParseURL(url, protocol, port, host, document));
			BOOST_CHECK_EQUAL(port, 443);
		}
		BOOST_AUTO_TEST_CASE(testFtpPort)
		{
			string url = "ftp://example.com";
			BOOST_CHECK(ParseURL(url, protocol, port, host, document));
			BOOST_CHECK_EQUAL(port, 21);
		}
		BOOST_AUTO_TEST_CASE(testMaxPort)
		{
			string url = "http://example.com:65535";
			BOOST_CHECK(ParseURL(url, protocol, port, host, document));
			BOOST_CHECK_EQUAL(port, 65535);
		}
		BOOST_AUTO_TEST_CASE(testMinPort)
		{
			string url = "http://example.com:1";
			BOOST_CHECK(ParseURL(url, protocol, port, host, document));
			BOOST_CHECK_EQUAL(port, 1);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(testCaseSensitive)
	{
		BOOST_CHECK(ParseURL("HTTP://example.com", protocol, port, host, document));
		BOOST_CHECK_EQUAL(protocol, Protocol::HTTP);
		BOOST_CHECK(ParseURL("hTtPs://example.com", protocol, port, host, document));
		BOOST_CHECK_EQUAL(protocol, Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_SUITE(testInvalid)
		BOOST_AUTO_TEST_CASE(testEmpty)
		{
			string url = "";
			BOOST_CHECK(!ParseURL(url, protocol, port, host, document));
		}
		BOOST_AUTO_TEST_CASE(testInvalidProtocol)
		{
			string url = "hppt://example.com";
			BOOST_CHECK(!ParseURL(url, protocol, port, host, document));
		}
		BOOST_AUTO_TEST_CASE(testInvalidMaxPort)
		{
			string url = "http://example.com:65536";
			BOOST_CHECK(!ParseURL(url, protocol, port, host, document));
		}
		BOOST_AUTO_TEST_CASE(testNullPort)
		{
			string url = "http://example.com:0000";
			BOOST_CHECK(!ParseURL(url, protocol, port, host, document));
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
