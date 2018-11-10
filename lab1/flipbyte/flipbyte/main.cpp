#include "logic.cpp"
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	uint8_t number;
	try
	{
		if (argc < 2)
		{
			throw invalid_argument("Not enough argument. Required 1 number in range [0..255] for program");
		}
		number = GetInputByte(argv[1]);
	}
	catch (const exception & ex)
	{
		cerr << ex.what() << endl;
		return 1;
	}
	number = GetFlipedByte(number);
	cout << number << endl;
}