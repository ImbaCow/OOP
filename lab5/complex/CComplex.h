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

	friend CComplex operator+(const CComplex& a, const CComplex& b);
	CComplex operator+() const;
	CComplex operator+=(const CComplex& b);

	friend CComplex operator-(const CComplex& a, const CComplex& b);
	CComplex operator-() const;
	CComplex operator-=(const CComplex& b);

	friend CComplex operator*(const CComplex& a, const CComplex& b);
	CComplex operator*=(const CComplex& b);

	friend CComplex operator/(const CComplex& a, const CComplex& b);
	CComplex operator/=(const CComplex& b);

	friend bool operator==(const CComplex& a, const CComplex& b);
	friend bool operator!=(const CComplex& a, const CComplex& b);

	friend std::ostream& operator<<(std::ostream& out, const CComplex& b);
	friend std::istream& operator>>(std::istream& in, CComplex& b);

private:
	double m_real;
	double m_imag;

	static std::string doubleToString(double num);
};
