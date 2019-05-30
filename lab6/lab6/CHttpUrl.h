#pragma once
	
class CHttpUrl
{
public:
	enum Protocol
	{
		HTTP,
		HTTPS
	};

	CHttpUrl(const std::string& url);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = HTTP);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

	static std::string ProtocolToString(Protocol protocol);

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	void ParseURL(const std::string& urlString);

	static unsigned short GetDefaultPort(Protocol protocol);
	static Protocol ProtocolFromString(const std::string& protocolString);
	static std::string DocumentFromString(std::string documentString);
	static unsigned short PortFromString(const std::string& portString, Protocol protocol);
};
