#include "pch.h"
//#include "CMyString.h"

using namespace std;

int main()
{
	char* ptr = new char[6]{ "hello" };
	cout << &ptr << endl;
	char* ptr2 = std::move(ptr);
	cout << &ptr << endl;
	cout << &ptr2 << endl;
}
