#include "pch.h"
#include "Field.h"

using namespace std;

int main()
{
	string inputName;
	cout << "Enter input file name" << endl;
	cin >> inputName;
	ifstream input(inputName);
	if (!input.is_open())
	{
		cerr << "Input file not found" << endl;
		return 1;
	}

	string outputName;
	cout << "Enter output file name" << endl;
	cin >> outputName;
	ofstream output(outputName);
	if (!output.is_open())
	{
		cerr << "Output file not found" << endl;
		return 1;
	}

	Field field(input);
	field.Fill();
	output << field.ToString() << endl;
}
