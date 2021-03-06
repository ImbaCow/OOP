#include "pch.h"

using namespace std;

struct EquationRoot4
{
	double numRoots;
	double roots[4];
};

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	double a2 = b / a;
	double b2 = c / a;
	double c2 = d / a;
	double d2 = e / a;

	return SolveReduced4(a2, b2, c2, d2);
}

EquationRoot4 SolveReduced4(double a, double b, double c, double d)
{

	double p = b - 3 * std::pow(a, 2) / 8;
	double q = std::pow(a, 3) / 8 - a * b / 2 + c;
	double r = -3 * std::pow(a, 4) / 256 + std::pow(a, 2) * b / 16 - c * a / 4 + d;
}


int main()
{
}
