#include "pch.h"
#include "URL.h"

const std::string PROTOCOL_REGEX = R"((?:(https?|ftp):\/\/)?)";
const std::string HOST_REGEX = R"(([^:\s\/\\?#]+))";
const std::string PORT_REGEX = R"((?::(?:0*([1-5][0-9]{4}|6(?:[0-4][0-9]{3}|5(?:[0-4][0-9]{2}|5(?:[0-2][0-9]|3[0-5])))|[1-9][0-9]{0,3})))?)";
const std::string PATH_REGEX = R"((?:\/((?:[^:\/\\?#]+\/?)*))?)";

const std::string URL_REGEX_PATTERN = "^%s%s%s%s$";

const size_t DEFAULT_HTTP_PORT = 80;
const size_t DEFAULT_HTTPS_PORT = 443;
const size_t DEFAULT_FTP_PORT = 21;

const size_t MIN_PORT = 1;
const size_t MAX_PORT = 65535;

int GetDefaultProtocol(const Protocol& protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return DEFAULT_HTTP_PORT;
	case Protocol::HTTPS:
		return DEFAULT_HTTPS_PORT;
	case Protocol::FTP:
		return DEFAULT_FTP_PORT;
	}
	throw std::invalid_argument("Unhandled port given");
}

Protocol ProtocolFromString(const std::string& str)
{
	std::string lowerStr(boost::to_lower_copy<std::string>(str));	

	if (lowerStr == "http" || lowerStr.empty())
	{
		return Protocol::HTTP;
	}
	if (lowerStr == "https")
	{
		return Protocol::HTTPS;
	}
	if (lowerStr == "ftp")
	{
		return Protocol::FTP;
	}
	throw std::invalid_argument("Wrong protocol given: " + lowerStr);
}

int PortFromString(const std::string& str, const Protocol& protocol)
{
	if (str.empty())
	{
		return GetDefaultProtocol(protocol);
	}
	int port = 0;
	try
	{
		port = boost::lexical_cast<int>(str);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Wrong port given: " + str);
	}

	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw std::out_of_range("Port must be in range " + std::to_string(MIN_PORT) + "-" + std::to_string(MAX_PORT) + ", '" + str + "' given");
	}

	return port;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::string regexStr = (boost::format(URL_REGEX_PATTERN) % PROTOCOL_REGEX % HOST_REGEX % PORT_REGEX % PATH_REGEX).str();
	std::regex reg(regexStr, std::regex_constants::icase);
	std::cmatch match;
	if (std::regex_match(url.c_str(), match, reg))
	{
		protocol = ProtocolFromString(std::string(match[1].first, match[1].second));
		host = std::string(match[2].first, match[2].second);
		port = PortFromString(std::string(match[3].first, match[3].second), protocol);
		document = std::string(match[4].first, match[4].second);
		return true;
	}
	return false;
}
