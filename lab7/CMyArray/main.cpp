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

void fun()
{
	HumanContact humanArr[] = { { "Common name", "8921822", "e.e@e.e" }, { "Common name 2", "8921821", "d.d@d.d" }, { "Common name 3", "89218221", "dd.dd@dd.dd" } };
	CMyArray<HumanContact> arr(humanArr, 3);
	cout << arr[2].phone;
	int intArr[] = { 1, 2, 3 };
	CMyArray<int> arr2(intArr, 3);
	cout << arr[2].phone << arr2[0];
}

int main()
{
	fun();
	HumanContact humanArr[] = { { "Common name", "8921822", "e.e@e.e" }, { "Common name 2", "8921821", "d.d@d.d" }, { "Common name 3", "89218221", "dd.dd@dd.dd" } };
	CMyArray<HumanContact> arr(humanArr, 3);
	cout << arr[2].phone;
}
