#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void JoinInputFile(const string & inputName, ofstream & output)
{
	ifstream input(inputName, ios::binary);
	if (!input.is_open())
	{
		throw invalid_argument("Input file '" + inputName + "' not found");
	}
	char ch;
	while (input.get(ch))
	{
		output << ch;
	}
}

void MergeInputFiles(int numberOffArguments, char * argArray[])
{
	const size_t outputFileIndex = numberOffArguments - 1;
	ofstream output(argArray[outputFileIndex], ios::binary);
	if (!output.is_open())
	{
		throw invalid_argument("No such output file directory was found");
	}
	for (size_t i = 1; i < outputFileIndex; ++i)
	{
		JoinInputFile(string(argArray[i]), output);
	}
}

int main(int argc, char * argv[])
{
	try
	{
		if (argc < 3)
		{
			throw  invalid_argument("Not enough arguments. You need at least 2 file name in format: <input file1> ... <input file N> <output file>");
		}
		MergeInputFiles(argc, argv);
	}
	catch (const exception & ex)
	{
		cerr << ex.what() << endl;
		return 1;
	}
}
