#include "pch.h"
#include "CMyArrayIterator.h"
#include "CMyArray.h"
#include "CMyArray.cpp"

using namespace std;

struct HumanContact
{
	std::string fullName;
	std::string phone;
	std::string email;
};

void funHuman()
{
	HumanContact humanArr[] = { { "Common name", "8921822", "e.e@e.e" }, { "Common name 2", "8921821", "d.d@d.d" }, { "Common name 3", "89218221", "dd.dd@dd.dd" } };
	CMyArray<HumanContact> arr(humanArr, 3);
	cout << arr[2].phone << endl;
}

void funString()
{
	string stringArr[] = { "strin1", "strin2", "strin3" };
	CMyArray<string> arr(stringArr, 3);
	cout << arr[2] << endl;
}

void funFloat()
{
	double floatArr[] = { 1.1, 2.2, 3.3 };
	CMyArray<double> arr(floatArr, 3);
	cout << arr[2] << endl;
}

int main()
{
	funHuman();
	funString();
	funFloat();
}
