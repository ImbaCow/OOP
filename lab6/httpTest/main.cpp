#include "pch.h"
#include "../lab6/CHttpUrl.h"
#include "../lab6/CUrlParsingError.h"

#define BOOST_TEST_MODULE HttpTest
#include "boost/test/unit_test.hpp"

using namespace std;

struct UrlTestFixture
{
	void TestUrl(const string& urlString, CHttpUrl::Protocol expectedProtocol, const string& expectedDomain, unsigned short expectedPort, const string& expectedDocument)
	{
		CHttpUrl url(urlString);
		BOOST_CHECK_EQUAL(url.GetProtocol(), expectedProtocol);
		BOOST_CHECK_EQUAL(url.GetDomain(), expectedDomain);
		BOOST_CHECK_EQUAL(url.GetPort(), expectedPort);
		BOOST_CHECK_EQUAL(url.GetDocument(), expectedDocument);
	}
};

BOOST_FIXTURE_TEST_SUITE(testParser, UrlTestFixture)

	BOOST_AUTO_TEST_SUITE(testValid)
		BOOST_AUTO_TEST_CASE(testFullUrl)
		{
			TestUrl("https://example.com:8000/doc/as", CHttpUrl::Protocol::HTTPS, "example.com", 8000, "/doc/as");
		}
		BOOST_AUTO_TEST_CASE(testDefaultProtocolUrl)
		{
			TestUrl("example.com:8000/doc/as", CHttpUrl::Protocol::HTTP, "example.com", 8000, "/doc/as");
		}
		BOOST_AUTO_TEST_CASE(testDefaultPortUrl)
		{
			TestUrl("https://example.com/doc/as", CHttpUrl::Protocol::HTTPS, "example.com", 443, "/doc/as");
			TestUrl("http://example.com/doc/as", CHttpUrl::Protocol::HTTP, "example.com", 80, "/doc/as");
		}
		BOOST_AUTO_TEST_CASE(testMinUrl)
		{
			TestUrl("example.com", CHttpUrl::Protocol::HTTP, "example.com", 80, "/");
		}
		BOOST_AUTO_TEST_CASE(testCaseInsensitive)
		{
			TestUrl("HTTp://example.com", CHttpUrl::Protocol::HTTP, "example.com", 80, "/");
		}
		BOOST_AUTO_TEST_CASE(testPortPredel)
		{
			TestUrl("HTTp://example.com:65535", CHttpUrl::Protocol::HTTP, "example.com", 65535, "/");
			TestUrl("HTTp://example.com:1", CHttpUrl::Protocol::HTTP, "example.com", 1, "/");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(testInvalid)
		BOOST_AUTO_TEST_CASE(testUnhandledProtocol)
		{
			BOOST_CHECK_THROW(CHttpUrl url("hppt://example.com"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(testPortPredel)
		{
			BOOST_CHECK_THROW(CHttpUrl url("http://example.com:65536"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl url("http://example.com:0"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(testInvalidFormat)
		{
			BOOST_CHECK_THROW(CHttpUrl url("example.com:400http://"), CUrlParsingError);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(testDocumentWithoutSlash)
	{
		CHttpUrl url("example.com", "doc", CHttpUrl::Protocol::HTTP);

		BOOST_CHECK_EQUAL(url.GetProtocol(), CHttpUrl::Protocol::HTTP);
		BOOST_CHECK_EQUAL(url.GetDomain(), "example.com");
		BOOST_CHECK_EQUAL(url.GetPort(), 80);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/doc");
		BOOST_CHECK_EQUAL(url.GetURL(), "http://example.com:80/doc");
	}
BOOST_AUTO_TEST_SUITE_END()
