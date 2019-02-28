#include "pch.h"
#include "CComplex.h"

CComplex::CComplex(double real, double imag)
	: m_real(real)
	, m_imag(imag)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_imag;
}

double CComplex::GetMagnitude() const
{
	return std::hypot(m_real, m_imag);
}

double CComplex::GetArgument() const
{
	if (m_real == 0 && m_imag == 0)
	{
		throw std::logic_error("Number must not be zero");
	}
	return std::atan2(m_imag, m_real);
}

CComplex CComplex::operator=(const CComplex& b)
{
	m_real = b.m_real;
	m_imag = b.m_imag;
	return *this;
}

std::string CComplex::ToString() const
{
	std::string result;

	if (m_imag == 0)
	{
		result += doubleToString(m_real);
	}
	else
	{
		if (m_real != 0)
		{
			result += doubleToString(m_real) + " + ";
		}
		result += doubleToString(m_imag) + 'i';
	}

	return result;
}

CComplex CComplex::operator+() const
{
	return *this;
}

CComplex CComplex::operator+=(const CComplex& b)
{
	*this = *this + b;
	return *this;
}

CComplex CComplex::operator-() const
{
	return { -m_real, -m_imag };
}

CComplex CComplex::operator-=(const CComplex& b)
{
	*this = *this - b;
	return *this;
}

CComplex CComplex::operator*=(const CComplex& b)
{
	*this = *this * b;
	return *this;
}

CComplex CComplex::operator/=(const CComplex& b)
{
	*this = *this / b;
	return *this;
}

std::string CComplex::doubleToString(double num)
{
	std::string numStr = std::to_string(num);
	numStr.resize(numStr.find_last_not_of('0') + 1);
	if (*numStr.rbegin() == '.')
	{
		numStr.pop_back();
	}

	return numStr;
}

CComplex operator+(const CComplex& a, const CComplex& b)
{
	return { a.Re() + b.Re(), a.Im() + b.Im() };
}

CComplex operator-(const CComplex& a, const CComplex& b)
{
	return a + (-b);
}

CComplex operator*(const CComplex& a, const CComplex& b)
{
	double newReal = a.Re() * b.Re() - a.Im() * b.Im();
	double newImag = a.Im() * b.Re() + a.Re() * b.Im();
	return { newReal, newImag };
}

CComplex operator/(const CComplex& a, const CComplex& b)
{
	if (b.Re() == 0 && b.Im() == 0)
	{
		throw std::logic_error("Second number must not be zero");
	}
	double newReal = (a.Re() * b.Re() + a.Im() * b.Im()) / (std::pow(b.Re(), 2) + std::pow(b.Im(), 2));
	double newImag = (a.Im() * b.Re() - a.Re() * b.Im()) / (std::pow(b.Re(), 2) + std::pow(b.Im(), 2));
	return { newReal, newImag };
}

bool operator==(const CComplex& a, const CComplex& b)
{
	bool realEqual = std::abs(a.Re() - b.Re()) < DBL_EPSILON;
	bool imagEqual = std::abs(a.Im() - b.Im()) < DBL_EPSILON;
	return realEqual && imagEqual;
}

bool operator!=(const CComplex& a, const CComplex& b)
{
	return !(a == b);
}

std::ostream& operator<<(std::ostream& out, const CComplex& b)
{
	out << b.ToString();
	return out;
}

std::istream& operator>>(std::istream& in, CComplex& b)
{
	double real, imag;
	char plus, i;

	if (!(in >> real
			&& in >> plus && plus == '+'
			&& in >> imag
			&& in >> i && i == 'i'))
	{
		throw std::invalid_argument("Invalid complex number");
	}

	b = { real, imag };
	return in;
}
