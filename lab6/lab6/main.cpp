#include "pch.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

int main()
{
	std::string urlString;
	while (cin >> urlString)
	{
		try
		{
			CHttpUrl url(urlString);
			cout << "Protocol: " << CHttpUrl::ProtocolToString(url.GetProtocol()) << endl;
			cout << "Domain: " << url.GetDomain() << endl;
			cout << "Port: " << url.GetPort() << endl;
			cout << "Document: " << url.GetDocument() << endl;
			cout << "URL: " << url.GetURL() << endl
				 << endl;
		}
		catch (const CUrlParsingError& e)
		{
			cout << e.what() << endl;
		}
	}
}
