#include "pch.h" 
#include "CComplex.h"

using namespace std;

int main()
{
	CComplex a, b;
	cout << "Enter two complex number for sum through space in format: \"%real% + %imag%i\"" << endl;
	try
	{
		cin >> a >> b;
		cout << "Sum: " << a + b << endl;
	}
	catch (const std::logic_error& e)
	{
		cerr << e.what() << endl;
	}
}
