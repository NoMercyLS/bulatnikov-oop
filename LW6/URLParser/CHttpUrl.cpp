#include "CHttpUrl.h"
using namespace ExceptionMessages;
CHttpUrl::CHttpUrl(std::string const& url)
{
	try
	{
		ParseUrl(url);
	}
	catch (const std::invalid_argument & e)
	{
		throw CUrlParsingError(e.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_domain(domain)
	, m_document(ParseDocument(document))
	, m_protocol(protocol)
{
	m_port = GetDefaultPort(protocol);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	, m_document(ParseDocument(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

std::string CHttpUrl::GetUrl() const
{
	std::string url = ProtocolToString(m_protocol) + "://" + m_domain;
	if (m_port != GetDefaultPort(m_protocol))
	{
		url += ":" + std::to_string(m_port);
	}
	return url + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(const std::string& url)
{
	if (url.empty())
	{
		throw std::invalid_argument(EMPTY_URL);
	}
	std::string urlString(url);

	std::string protocol = ParseProtocol(urlString);
	m_protocol = GetProtocolFromLine(protocol);

	size_t position = urlString.find("://") + 3;
	urlString = urlString.substr(position);
	m_domain = ParseDomain(urlString);
	urlString = urlString.substr(m_domain.size());

	position = urlString.find(":");
	if (position != std::string::npos)
	{
		m_port = ParsePort(urlString.substr(position));
		urlString = urlString.substr(std::to_string(m_port).size() + 1);
	}
	else
	{
		m_port = GetDefaultPort(m_protocol);
	}

	m_document = ParseDocument(urlString);
}

std::string CHttpUrl::ParseProtocol(const std::string& url)
{
	size_t endOfProtocol = url.find("://");
	if (endOfProtocol == std::string::npos)
	{
		throw std::invalid_argument(INVALID_PROTOCOL);
	}
	std::string protocol = boost::to_lower_copy(url.substr(0, endOfProtocol));
	GetProtocolFromLine(protocol);
	return protocol;
}

std::string CHttpUrl::ParseDomain(const std::string& url)
{
	size_t endOfDomain = url.find(":");
	if (endOfDomain == std::string::npos)
	{
		endOfDomain = url.find("/");
	}
	std::string domain = url.substr(0, endOfDomain);
	if (domain == "" || (domain.find(' ') != std::string::npos))
	{
		throw std::invalid_argument(INVALID_DOMAIN);
	}
	return domain;
}

unsigned short CHttpUrl::ParsePort(const std::string& url)
{
	size_t endOfPort = url.find("/");
	std::string portString = url.substr(1, endOfPort - 1);

	int port = 0;
	try
	{
		port = boost::lexical_cast<int>(portString);
	}
	catch (boost::bad_lexical_cast&)
	{
		throw std::invalid_argument(INVALID_PORT);
	}

	if (port < MIN_PORT_VALUE || port > MAX_PORT_VALUE)
	{
		throw std::invalid_argument(PORT_OUT_OF_RANGE);
	}
	unsigned short us_port = (unsigned short)port;
	return us_port;
}

std::string CHttpUrl::ParseDocument(const std::string& url)
{
	std::string document = (url[0] != '/') ? '/' + url : url;
	if (document.empty() || document.find(' ') != std::string::npos)
	{
		throw std::invalid_argument(INVALID_DOCUMENT);
	}
	return document;
}

Protocol CHttpUrl::GetProtocolFromLine(const std::string& protocol)
{
	if (protocol == HTTP_STRING)
	{
		return Protocol::HTTP;
	}
	if (protocol == HTTPS_STRING)
	{
		return Protocol::HTTPS;
	}
	throw std::invalid_argument(INVALID_PROTOCOL_TYPE);
}

std::string CHttpUrl::ProtocolToString(const Protocol& protocol)
{
	return (protocol == Protocol::HTTP) ? HTTP_STRING : HTTPS_STRING;
}

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol)
{
	return (protocol == Protocol::HTTP) ? HTTP_DEFAULT_PORT : HTTPS_DEFAULT_PORT;
}

std::string GetInfo(const CHttpUrl& url)
{
	std::ostringstream strm;
	strm << "URL: " << url.GetUrl() << std::endl
		<< "\tProtocol: " << url.ProtocolToString(url.GetProtocol()) << std::endl
		<< "\tDomain: " << url.GetDomain() << std::endl
		<< "\tPort: " << url.GetPort() << std::endl
		<< "\tDocument: " << url.GetDocument() << std::endl;
	return strm.str();
}