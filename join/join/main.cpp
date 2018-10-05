// Вариант 5. Программа join. Слияние входных файлов в один выходной

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		ofstream output(argv[argc - 1], ios::binary);
		if (!output.is_open())
		{
			cout << "Output file dir not found" << endl;
			exit(0);
		}
		for (size_t i = 1; i < argc - 1; ++i)
		{
			ifstream input(argv[i], ios::binary);
			if (!input.is_open())
			{
				cout << "Input file \"" << argv[i] << "\" not found" << endl;
				exit(0);
			}
			char* ch = new char;
			while (input.read(ch, sizeof(char)))
			{
				output.write(ch, sizeof(char));
			}
			input.close();
			delete ch;
		}
		output.close();
	}
	else
	{
		cout << "Not enough arg" << endl;
	}
}