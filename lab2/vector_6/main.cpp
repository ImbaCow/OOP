#include "pch.h"
#include "MyArray.h"

using namespace std;

int main()
{
	MyArray array;
	string input;
	getline(cin, input);

	array.AddItemsFromString(input);
	array.ProcessArray();
	array.SortArray();
	cout << array.ReturnByString() << endl;
}
