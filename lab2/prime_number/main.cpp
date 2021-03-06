#include "pch.h"
#include "PrimeNumberUtils.h"
#include "boost/lexical_cast.hpp"

using namespace std;

optional<int> GetUpperBoundString(const string& upperBoundString)
{
	int upperBound;

	try
	{
		upperBound = boost::lexical_cast<uint32_t>(upperBoundString);
		return upperBound;
	}
	catch (const boost::exception&)
	{
		return nullopt;
	}
}

optional<string> GetPrimeNumbers(const string& upperBoundString)
{

	optional<int> upperBoundOpt = GetUpperBoundString(upperBoundString);
	if (!upperBoundOpt)
	{
		cerr << "Wrong type of argument, must have integer value";
		return nullopt;
	}

	try
	{
		return IntSetToString(GeneratePrimeNumbersSet(upperBoundOpt.value()));
	}
	catch (const std::invalid_argument& e)
	{
		cerr << e.what() << endl;
		return nullopt;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cerr << "Not enough argument, must have 1 integer value";
		return 1;
	}

	optional<string> primesOpt = GetPrimeNumbers(argv[1]);
	if (!primesOpt)
	{
		return 1;
	}
	cout << primesOpt.value() << endl;
}
