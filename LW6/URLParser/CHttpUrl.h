#pragma once
#include "CUrlParsingError.h"

enum class Protocol
{
	HTTP = 85,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(string const& url);
	CHttpUrl(
		string const& domain,
		string const& document,
		Protocol protocol = Protocol::HTTP
	);
	CHttpUrl(
		string const& domain,
		string const& document,
		Protocol protocol,
		unsigned short port
	);

	string GetUrl()const;
	string GetDomain()const;
	string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;
	static string ProtocolToString(const Protocol& protocol);
private:
	string m_url;
	string m_domain;
	string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	void ParseUrl(const string& url);
	static string ParseDomain(const string& url);
	static string ParseDocument(const string& url);
	static string ParseProtocol(const string& url);
	static unsigned short ParsePort(const string& url);
	static Protocol GetProtocolFromLine(const string& line);
	static unsigned short GetDefaultPort(Protocol protocol);
};

string GetInfo(const CHttpUrl& url);
