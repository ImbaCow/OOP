#include "pch.h"
#include "html_logic.h"

using namespace std;

int main()
{
	string str;
	while (getline(cin, str))
	{
		cout << HtmlEncode(str) << endl;
	}
}
