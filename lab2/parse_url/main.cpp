#include "pch.h"
#include "URL.h"

using namespace std;

int main()
{
	Protocol protocol;
	string host;
	int port;
	string document;

	string url = "https://example.com:8000/doc/as";

	assert(ParseURL(url, protocol, port, host, document));
	cout << protocol << endl;
	cout << host << endl;
	cout << port << endl;
	cout << document << endl;
}
