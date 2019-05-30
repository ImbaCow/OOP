#include "pch.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"


const std::string PROTOCOL_REGEX = R"((?:([a-z]+):\/\/)?)";
const std::string DOMAIN_REGEX = R"(([^:\s\/\\?#]+))";
const std::string PORT_REGEX = R"((?::(\d+))?)";
const std::string DOC_REGEX = R"((\/(?:[^:\/\\]*\/?)*)?)";

const std::string URL_REGEX_PATTERN = "^%s%s%s%s$";

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;

CHttpUrl::CHttpUrl(const std::string& url)
{
	try
	{
		ParseURL(url);
	}
	catch (const std::exception& e)
	{
		throw CUrlParsingError(e.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	, m_document(DocumentFromString(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

std::string CHttpUrl::GetURL() const
{
	std::string resultUrl = ProtocolToString(m_protocol) + "://" + m_domain + ':' + std::to_string(m_port) + m_document;
	return resultUrl;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseURL(const std::string& urlString)
{
	std::string formatedUrlString = boost::trim_copy(urlString);
	std::string regexStr = (boost::format(URL_REGEX_PATTERN) % PROTOCOL_REGEX % DOMAIN_REGEX % PORT_REGEX % DOC_REGEX).str();
	std::regex reg(regexStr, std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_match(formatedUrlString, match, reg))
	{
		throw CUrlParsingError("Unvalid URL format, expected: '[<protocol>://]<domain>[:<port>][/<document>]'");
	}

	m_protocol = ProtocolFromString(std::string(match[1].first, match[1].second));
	m_domain = std::string(match[2].first, match[2].second);
	m_port = PortFromString(std::string(match[3].first, match[3].second), m_protocol);
	m_document = DocumentFromString(std::string(match[4].first, match[4].second));
}

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol)
{
	unsigned short resultPort;
	switch (protocol)
	{
	case HTTP:
		resultPort = DEFAULT_HTTP_PORT;
		break;
	case HTTPS:
		resultPort = DEFAULT_HTTPS_PORT;
		break;
	default:
		throw std::invalid_argument("Unhandled protocol given: " + std::to_string(protocol));
	}

	return resultPort;
}

std::string CHttpUrl::ProtocolToString(Protocol protocol)
{
	std::string resultString;
	switch (protocol)
	{
	case HTTP:
		resultString = "http";
		break;
	case HTTPS:
		resultString = "https";
		break;
	default:
		throw std::invalid_argument("Unhandled protocol given: " + std::to_string(protocol));
	}

	return resultString;
}

CHttpUrl::Protocol CHttpUrl::ProtocolFromString(const std::string& protocolString)
{
	std::string lowerStr(boost::to_lower_copy<std::string>(protocolString));
	Protocol resultProtocol;

	if (lowerStr == "http" || lowerStr.empty())
	{
		resultProtocol = Protocol::HTTP;
	}
	else if (lowerStr == "https")
	{
		resultProtocol = Protocol::HTTPS;
	}
	else
	{
		throw std::invalid_argument("Wrong protocol given: " + lowerStr);
	}

	return resultProtocol;
}

std::string CHttpUrl::DocumentFromString(std::string documentString)
{
	if (documentString.empty() || documentString[0] != '/')
	{
		documentString.insert(0, "/");
	}
	return documentString;
}

unsigned short CHttpUrl::PortFromString(const std::string& portString, Protocol protocol)
{
	if (portString.empty())
	{
		return GetDefaultPort(protocol);
	}
	unsigned short port = 0;
	try
	{
		port = boost::lexical_cast<unsigned short>(portString);
	}
	catch (const boost::bad_lexical_cast&)
	{
	}
	if (port == 0)
	{
		throw std::invalid_argument("Wrong port given: " + portString);
	}
	return port;
}
