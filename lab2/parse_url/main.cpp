#include "pch.h"
#include "URL.h"

using namespace std;

int main()
{
	string line;
	while (getline(cin, line))
	{
		Protocol protocol;
		string host;
		int port;
		string document;

		if (!ParseURL(line, protocol, port, host, document))
		{
			cout << "Invalid url" << endl;
		}
		else
		{
			cout << "HOST: " << host << endl;
			cout << "PORT: " << port << endl;
			cout << "DOC: " << document << endl;
		}
		cout << endl;
	}
}
