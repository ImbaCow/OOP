#pragma once
class CComplex
{
public:
	CComplex(double real = 0, double image = 0);
	virtual ~CComplex(){};

	double Re() const;
	double Im() const;

	double GetMagnitude() const;
	double GetArgument() const;

	CComplex operator=(const CComplex& b);
	std::string ToString() const;

	CComplex operator+() const;
	CComplex operator+=(const CComplex& b);

	CComplex operator-() const;
	CComplex operator-=(const CComplex& b);

	CComplex operator*=(const CComplex& b);
	CComplex operator/=(const CComplex& b);

private:
	double m_real;
	double m_imag;

	static std::string doubleToString(double num);
};

CComplex operator-(const CComplex& a, const CComplex& b);
CComplex operator+(const CComplex& a, const CComplex& b);

CComplex operator*(const CComplex& a, const CComplex& b);
CComplex operator/(const CComplex& a, const CComplex& b);

bool operator==(const CComplex& a, const CComplex& b);
bool operator!=(const CComplex& a, const CComplex& b);

std::ostream& operator<<(std::ostream& out, const CComplex& b);
std::istream& operator>>(std::istream& in, CComplex& b);
