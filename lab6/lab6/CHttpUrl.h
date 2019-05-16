#pragma once
#include "CUrlParsingError.h"

enum Protocol
{
	HTTP,
	HTTPS
};

const std::string PROTOCOL_REGEX = R"((?:([a-z]+):\/\/)?)";
const std::string DOMAIN_REGEX = R"(([^:\s\/\\?#]+))";
const std::string PORT_REGEX = R"((?::(\d+))?)";
const std::string DOC_REGEX = R"((\/(?:[^:\/\\]*\/?)*)?)";

const std::string URL_REGEX_PATTERN = "^%s%s%s%s$";

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;

const size_t MIN_PORT = 1;
const size_t MAX_PORT = 65535;
	
class CHttpUrl
{
public:
	CHttpUrl(const std::string& url);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = HTTP);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	void ParseURL(const std::string& urlString);
	unsigned short GetDefaultPort(Protocol protocol) const;
	std::string ProtocolToString(Protocol protocol) const;
	Protocol ProtocolFromString(const std::string& protocolString) const;
	std::string DocumentFromString(std::string documentString) const;
	unsigned short PortFromString(const std::string& portString, Protocol protocol) const;
};
