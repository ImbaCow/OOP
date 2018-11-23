#include "pch.h"
#include "Matrix.h"

SquareMatrix3::SquareMatrix3(const std::string & inputFile)
{
	InitFromFile(inputFile);
}

SquareMatrix3::SquareMatrix3(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE> & matr)
{
	InitFromMatr(matr);
}

void SquareMatrix3::InitFromFile(const std::string & inputFile)
{
	std::ifstream input(inputFile);
	if (!input.is_open())
	{
		throw std::invalid_argument("Unavailable to open input file");
	}
	std::string line;
	size_t i = 0;
	while (std::getline(input, line))
	{
		size_t j = 0;
		double value;
		std::stringstream sstream(line);
		while (sstream >> value)
		{
			m_matr[i][j] = value;
			if (++j > MATR_SIZE)
			{
				throw std::invalid_argument("So many arguments on " + std::to_string(i) + " line. Matrix must be square with size = " + std::to_string(MATR_SIZE));
			}
		}
		if (j < MATR_SIZE)
		{
			throw std::invalid_argument("Not enough arguments on " + std::to_string(i) + " line. Matrix must be square with size = " + std::to_string(MATR_SIZE));
		}
		if (++i > MATR_SIZE)
		{
			throw std::invalid_argument("So many line in input file. Matrix must be square with size = " + std::to_string(MATR_SIZE));
		}
	}
	if (++i < MATR_SIZE)
	{
		throw std::invalid_argument("Not enough line in input file. Matrix must be square with size = " + std::to_string(MATR_SIZE));
	}
}

void SquareMatrix3::InitFromMatr(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE>& matr)
{
	m_matr = matr;
}

SquareMatrix3 * SquareMatrix3::Invert()
{
	m_matr = GetInvert(m_matr);
	return this;
}

SquareMatrix3 * SquareMatrix3::FindAdjugate()
{
	m_matr = GetAdjugate(m_matr);
	return this;
}

SquareMatrix3 * SquareMatrix3::Transpose()
{
	m_matr = GetTranspose(m_matr);
	return this;
}

template <std::size_t SIZE>
double SquareMatrix3::CalcDet(const MatrType<double, SIZE> & matr) const
{
	double det = 0;
	for (size_t j = 0; j < SIZE; ++j)
	{
 		det += pow((-1), j) * matr[0][j] * CalcDet(GetMinor(matr, 0, j));
	}
	return det;
}

template <>
double SquareMatrix3::CalcDet(const MatrType<double, 1> & matr) const
{
	return matr[0][0];
}

template <std::size_t SIZE>
SquareMatrix3::MatrType<double, SIZE - 1> SquareMatrix3::GetMinor(const MatrType<double, SIZE> & matr, size_t i, size_t j) const
{
	if (!(i < SIZE && j < SIZE))
	{
		throw std::logic_error("Not correct line index in GetMinor!");
	}
	MatrType<double, SIZE - 1> minor = { {0} };
	for (size_t ti = 0, mi = 0; ti < SIZE; ++ti, ++mi)
	{
		if (ti == i)
		{
			++ti;
		}
		for (size_t tj = 0, mj = 0; tj < SIZE; ++tj, ++mj)
		{
			if (tj == j)
			{
				++tj;
			}
			if (ti < SIZE && tj < SIZE)
			{
				minor[mi][mj] = matr[ti][tj];
			}
		}
	}
	return minor;
}

SquareMatrix3::MatrType<double, SquareMatrix3::MATR_SIZE> SquareMatrix3::GetAdjugate(const MatrType<double, MATR_SIZE> & matr) const
{
	MatrType<double, MATR_SIZE> adjugate = { {0} };
	for (size_t i = 0; i < MATR_SIZE; ++i)
	{
		for (size_t j = 0; j < MATR_SIZE; ++j)
		{
			adjugate[i][j] = pow(-1, (i + j)) * CalcDet(GetMinor(matr, i, j));
		}
	}
	return GetTranspose(adjugate);
}

SquareMatrix3::MatrType<double, SquareMatrix3::MATR_SIZE> SquareMatrix3::GetTranspose(const MatrType<double, MATR_SIZE>& matr) const
{
	MatrType<double, MATR_SIZE> transpose = { {0} };
	for (size_t i = 0; i < MATR_SIZE; ++i)
	{
		for (size_t j = 0; j < MATR_SIZE; ++j)
		{
			transpose[i][j] = matr[j][i];
		}
	}
	return transpose;
}

SquareMatrix3::MatrType<double, SquareMatrix3::MATR_SIZE> SquareMatrix3::GetInvert(const MatrType<double, MATR_SIZE>& matr) const
{
	double det = CalcDet(matr);
	if (det == 0)
	{
		throw std::logic_error("Unable to calculate inverse matrix, determinant is 0");
	}
	MatrType<double, MATR_SIZE> invert = GetAdjugate(matr);
	for (auto & line : invert)
	{
		for (auto & value : line)
		{
			value /= det;
		}
	}
	return invert;
}

void SquareMatrix3::WriteMatr(std::ostream & stream)
{
	stream << std::setprecision(PRECISION) << std::fixed;
	for (const auto & line : m_matr)
	{
		for (const auto & value : line)
		{
			stream << value << ' ';
		}
		stream << std::endl;
	}
}

double SquareMatrix3::GetDeterminant()
{
	return CalcDet(m_matr);
}
