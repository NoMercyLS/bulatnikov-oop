#pragma once
#include "source.h"
#include "const.h"
#include "CUrlParsingError.h"
enum class Protocol
{
	HTTP = 85,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP
	);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port
	);

	std::string GetUrl()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;
	static std::string ProtocolToString(const Protocol& protocol);
private:
	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	void ParseUrl(const std::string& url);
	static std::string ParseDomain(const std::string& url);
	static std::string ParseDocument(const std::string& url);
	static std::string ParseProtocol(const std::string& url);
	static unsigned short ParsePort(const std::string& url);
	static Protocol GetProtocolFromLine(const std::string& line);
	static unsigned short GetDefaultPort(Protocol protocol);
};

std::string GetInfo(const CHttpUrl& url);
