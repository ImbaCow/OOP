
// Вариант 5. Программа flipbyte. Битовый зеркальный разворот входного числа и вывод результата в 10 системе счисления.
#include <cstdint>
#include <iostream>

using namespace std;

uint8_t getInputByte(int argc, char* argv[])
{
	uint8_t res;
	try
	{
		if (argc < 2)
		{
			throw exception("Not enough arg");
		}
		int number = stoi(argv[1]);
		if (number >= 0 && number < 256)
		{
			res = static_cast<uint8_t>(number);
		}
		else
		{
			throw exception("Arg out of range [0..255]");
		}
	}
	catch (const std::exception& exception)
	{
		cout << exception.what() << endl;
		exit(0);
	}
	return res;
}

uint8_t getFlipedByte(uint8_t byte)
{
	uint8_t res = 0;
	for (size_t i = 0; i < 8; ++i)
	{
		if (byte & (1 << (7 - i)))
		{
			res += 1 << i;
		}
	}
	return res;
}

int main(int argc, char* argv[])
{
	int number = getInputByte(argc, argv);
	int flippedNumber = getFlipedByte(number);
	cout << flippedNumber << endl;
	return 0;
}