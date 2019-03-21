#include "pch.h"
#include "WordsMap.h"

using namespace std;

int main()
{
	cout << "Enter words list, enter Ctrl + Z for result." << endl;
	auto wordsMap = CreateWordsMap(cin);
	cout << WordsMapToString(wordsMap) << endl;
}
