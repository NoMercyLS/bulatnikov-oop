#define BOOST_TEST_MODULE UnitTests
#define BOOST_ALL_NO_LIB
#define BOOST_TEST_MAIN
#include "boost/test/unit_test.hpp"
#include "../URLParser/CHttpUrl.h"
#include "../URLParser/CUrlParsingError.h"
#include "../URLParser/const.h"

void VerifyURL(CHttpUrl url
	, std::string const& expectedDomain
	, std::string const& expectedDocument
	, Protocol expectedProtocol
	, unsigned short expectedPort)
{
	BOOST_CHECK(url.GetDomain() == expectedDomain);
	BOOST_CHECK(url.GetDocument() == expectedDocument);
	BOOST_CHECK(url.GetProtocol() == expectedProtocol);
	BOOST_CHECK(url.GetPort() == expectedPort);
}

void VerifyURLString(CHttpUrl url, std::string const& urlString)
{
	BOOST_CHECK(url.GetUrl() == urlString);
}

BOOST_AUTO_TEST_SUITE(HTTP_URL_can_get)

BOOST_AUTO_TEST_CASE(info_from_right_url)
{
	CHttpUrl url("http://google.com:85/in.html");
	CHttpUrl url2("http://google.com:85/files/in.html");
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTP, 85);
	VerifyURL(url2, "google.com", "/files/in.html", Protocol::HTTP, 85);
}

BOOST_AUTO_TEST_CASE(port_80_from_url)
{
	CHttpUrl url("http://google.com/in.html");
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTP, HTTP_DEFAULT_PORT);
}

BOOST_AUTO_TEST_CASE(url_without_default_port)
{
	CHttpUrl url("http://google.com/in.html");
	BOOST_CHECK(url.GetPort() == HTTP_DEFAULT_PORT);
	VerifyURLString(url, "http://google.com/in.html");
}

BOOST_AUTO_TEST_CASE(url_with_port)
{
	CHttpUrl url("http://google.com:85/in.html");
	VerifyURLString(url, "http://google.com:85/in.html");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(HTTPS_URL_can_get)

BOOST_AUTO_TEST_CASE(info_from_right_url)
{
	CHttpUrl url("https://google.com:85/in.html");
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTPS, 85);
}

BOOST_AUTO_TEST_CASE(port_443_from_url)
{
	CHttpUrl url("https://google.com/in.html");
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTPS, HTTPS_DEFAULT_PORT);
}

BOOST_AUTO_TEST_CASE(url_without_default_port)
{
	CHttpUrl url("https://google.com/in.html");
	BOOST_CHECK(url.GetPort() == HTTPS_DEFAULT_PORT);
	VerifyURLString(url, "https://google.com/in.html");
}

BOOST_AUTO_TEST_CASE(url_with_port)
{
	CHttpUrl url("https://google.com:85/in.html");
	VerifyURLString(url, "https://google.com:85/in.html");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(Can_add_slash_to_document)
{
	CHttpUrl url("http://google.com");
	BOOST_CHECK(url.GetDocument() == "/");
}

BOOST_AUTO_TEST_SUITE(Can_print_info_)
BOOST_AUTO_TEST_CASE(about_http_url)
{
	CHttpUrl url("http://google.com:85/in.html");
	string expectedString = R"(URL: http://google.com:85/in.html
	Protocol: http
	Domain: google.com
	Port: 85
	Document: /in.html
)";
	BOOST_CHECK_EQUAL(expectedString, GetInfo(url));
}
BOOST_AUTO_TEST_CASE(about_https_url)
{
	CHttpUrl url("https://google.com:85/in.html");
	string expectedString = R"(URL: https://google.com:85/in.html
	Protocol: https
	Domain: google.com
	Port: 85
	Document: /in.html
)";
	BOOST_CHECK_EQUAL(expectedString, GetInfo(url));
}
BOOST_AUTO_TEST_CASE(about_url_with_entered_default_port)
{
	CHttpUrl url("http://google.com:80/in.html");
	string expectedString = R"(URL: http://google.com/in.html
	Protocol: http
	Domain: google.com
	Port: 80
	Document: /in.html
)";
	BOOST_CHECK_EQUAL(expectedString, GetInfo(url));
}
BOOST_AUTO_TEST_CASE(about_url_with_default_port)
{
	CHttpUrl url("http://google.com/in.html");
	string expectedString = R"(URL: http://google.com/in.html
	Protocol: http
	Domain: google.com
	Port: 80
	Document: /in.html
)";
	BOOST_CHECK_EQUAL(expectedString, GetInfo(url));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(URL_constructed_)
BOOST_AUTO_TEST_CASE(with_domain_and_document)
{
	CHttpUrl url("google.com", "in.html");
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTP, HTTP_DEFAULT_PORT);
	VerifyURLString(url, "http://google.com/in.html");
}

BOOST_AUTO_TEST_CASE(with_different_protocol_register)
{
	CHttpUrl urlHttp("HtTp://google.com/in.html");
	VerifyURL(urlHttp, "google.com", "/in.html", Protocol::HTTP, HTTP_DEFAULT_PORT);
	VerifyURLString(urlHttp, "http://google.com/in.html");

	CHttpUrl urlHttps("HtTpS://google.com/in.html");
	VerifyURL(urlHttps, "google.com", "/in.html", Protocol::HTTPS, HTTPS_DEFAULT_PORT);
	VerifyURLString(urlHttps, "https://google.com/in.html");
}

BOOST_AUTO_TEST_CASE(with_http_protocol_and_domain_and_document)
{
	CHttpUrl url("google.com", "in.html", Protocol::HTTP);
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTP, HTTP_DEFAULT_PORT);
	VerifyURLString(url, "http://google.com/in.html");
}
BOOST_AUTO_TEST_CASE(with_https_protocol_and_domain_and_document)
{
	CHttpUrl url("google.com", "in.html", Protocol::HTTPS);
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTPS, HTTPS_DEFAULT_PORT);
	VerifyURLString(url, "https://google.com/in.html");
}
BOOST_AUTO_TEST_CASE(with_http_protocol_and_domain_and_document_and_port)
{
	CHttpUrl url("google.com", "in.html", Protocol::HTTP, 85);
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTP, 85);
	VerifyURLString(url, "http://google.com:85/in.html");
}
BOOST_AUTO_TEST_CASE(with_https_protocol_and_domain_and_document_and_port)
{
	CHttpUrl url("google.com", "in.html", Protocol::HTTPS, 85);
	VerifyURL(url, "google.com", "/in.html", Protocol::HTTPS, 85);
	VerifyURLString(url, "https://google.com:85/in.html");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Exceptions_are_thrown_when)
BOOST_AUTO_TEST_CASE(url_is_empty)
{
	BOOST_CHECK_THROW(CHttpUrl url(""), CUrlParsingError);
}

BOOST_AUTO_TEST_CASE(protocol_is_empty)
{
	BOOST_CHECK_THROW(CHttpUrl url("google.com:85/in.html"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(protocol_is_not_http_or_https)
{
	BOOST_CHECK_THROW(CHttpUrl url("ht://google.com:85/in.html"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(protocol_has_wrong_format)
{
	BOOST_CHECK_THROW(CHttpUrl url("http:://google.com/in.html"), CUrlParsingError);
	BOOST_CHECK_THROW(CHttpUrl url("http:/google.com/in.html"), CUrlParsingError);
	BOOST_CHECK_THROW(CHttpUrl url("http:///google.com/in.html"), CUrlParsingError);
	BOOST_CHECK_THROW(CHttpUrl url("http:google.com/in.html"), CUrlParsingError);
	BOOST_CHECK_THROW(CHttpUrl url("http/google.com/in.html"), CUrlParsingError);
}

BOOST_AUTO_TEST_CASE(domain_is_empty)
{
	BOOST_CHECK_THROW(CHttpUrl url("http://:85/in.html"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(domain_has_spaces)
{
	BOOST_CHECK_THROW(CHttpUrl url("http://go ogle.com:85/in.html"), CUrlParsingError);
}

BOOST_AUTO_TEST_CASE(document_has_spaces)
{
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:85/in dex.html"), CUrlParsingError);
}

BOOST_AUTO_TEST_CASE(port_is_empty)
{
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:/in.html"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(port_is_incorrect)
{
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:85:85/in.html"), CUrlParsingError);
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:fhg/in.html"), CUrlParsingError);
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:85d5/in.html"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(port_is_less_than_1)
{
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:0/in.html"), CUrlParsingError);
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:-45/in.html"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(port_is_greater_than_65535)
{
	BOOST_CHECK_THROW(CHttpUrl url("http://google.com:65536/in.html"), CUrlParsingError);
}

BOOST_AUTO_TEST_SUITE_END()