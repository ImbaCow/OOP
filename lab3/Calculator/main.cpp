#include "pch.h"
#include "ConsoleCalculator.h"

using namespace std;

int main()
{
	ConsoleCalculator calc(cin, cout);
	calc.Start();
/*
	Calculator calc;
	calc.Let("variable", 1);
	calc.Fn("fn0", "variable");
	for (size_t i = 1; i < 1000000; ++i)
	{
		string previousFnName = "fn" + to_string(i - 1);
		string currentFnName = "fn" + to_string(i);
		calc.Fn(currentFnName, previousFnName, "variable", BinarOperator::PLUS);
	}

	stringstream ss("");
	calc.Print("fn999999", cout);

	calc.Let("variable", 2);*/
}
