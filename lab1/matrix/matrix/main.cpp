#include "pch.h"
#include "Matrix.h"

using namespace std;

int main()
{
	try
	{
		SquareMatrix3 matrix;
		matrix.InitFromFile("input.txt");
		cout << "Input matrix" << endl;
		matrix.WriteMatr(cout);
		cout << endl << "Inverted matrix" << endl;
		matrix.Invert();
		matrix.WriteMatr(cout);
	}
	catch (const exception & ex)
	{
		cerr << ex.what() << endl;
		return 1;
	}
}
