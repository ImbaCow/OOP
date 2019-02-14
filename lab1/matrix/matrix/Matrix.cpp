#include "pch.h"
#include "Matrix.h"

namespace
{
	const size_t PRECISION = 3;
}

template<std::size_t MATR_SIZE>
SquareMatrix<MATR_SIZE>::SquareMatrix()
	:m_matr(NULL_MATR)
{
}

template<std::size_t MATR_SIZE>
SquareMatrix<MATR_SIZE>::SquareMatrix(const std::string & inputFile)
{
	SetFromFile(inputFile);
}

template<std::size_t MATR_SIZE>
SquareMatrix<MATR_SIZE>::SquareMatrix(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE> & matr)
{
	SetFromMatr(matr);
}

template<std::size_t MATR_SIZE>
void SquareMatrix<MATR_SIZE>::SetFromFile(const std::string & inputFileName)
{
	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		throw std::invalid_argument("Unavailable to open input file: '" + inputFileName + "'");
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
			++j;
			if (j > MATR_SIZE)
			{
				throw std::invalid_argument("So many arguments on " + std::to_string(i) + " line. Matrix must be square with size = " + std::to_string(MATR_SIZE));
			}
		}
		++i;
		if (j < MATR_SIZE)
		{
			throw std::invalid_argument("Not enough arguments on " + std::to_string(i) + " line. Matrix must be square with size = " + std::to_string(MATR_SIZE));
		}
		if (i > MATR_SIZE)
		{
			throw std::invalid_argument("So many line in input file. Matrix must be square with size = " + std::to_string(MATR_SIZE));
		}
	}
	if (i < MATR_SIZE)
	{
		throw std::invalid_argument("Not enough line in input file. Matrix must be square with size = " + std::to_string(MATR_SIZE));
	}
}

template<std::size_t MATR_SIZE>
void SquareMatrix<MATR_SIZE>::SetFromMatr(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE>& matr)
{
	m_matr = matr;
}

template<std::size_t MATR_SIZE>
void SquareMatrix<MATR_SIZE>::Invert()
{
	m_matr = GetInvert(m_matr);
}

template<std::size_t MATR_SIZE>
void SquareMatrix<MATR_SIZE>::Adjugate()
{
	m_matr = GetAdjugate(m_matr);
}

template<std::size_t MATR_SIZE>
void SquareMatrix<MATR_SIZE>::Transpose()
{
	m_matr = GetTranspose(m_matr);
}

template<std::size_t MATR_SIZE>
template <std::size_t SIZE>
double SquareMatrix<MATR_SIZE>::CalcDet(const MatrType<double, SIZE> & matr) const
{
	double det = 0;
	for (size_t j = 0; j < SIZE; ++j)
	{
 		det += pow((-1), j) * matr[0][j] * CalcDet(GetMinor(matr, 0, j));
	}
	return det;
}

template<std::size_t MATR_SIZE>
template<>
double SquareMatrix<MATR_SIZE>::CalcDet(const MatrType<double, 1> & matr) const
{
	return matr[0][0];
}

template<std::size_t MATR_SIZE>
template <std::size_t SIZE>
SquareMatrix<MATR_SIZE>::MatrType<double, SIZE - 1> SquareMatrix<MATR_SIZE>::GetMinor(const MatrType<double, SIZE> & matr, size_t line, size_t collumn) const
{
	if (!(line < SIZE && collumn < SIZE))
	{
		throw std::logic_error("Not correct line index in GetMinor!");
	}
	MatrType<double, SIZE - 1> minor = { {0} };
	for (size_t matrLine = 0, minorLine = 0; matrLine < SIZE; ++matrLine, ++minorLine)
	{
		if (matrLine == line)
		{
			++matrLine;
		}
		for (size_t matrCollumn = 0, minorCollumn = 0; matrCollumn < SIZE; ++matrCollumn, ++minorCollumn)
		{
			if (matrCollumn == collumn)
			{
				++matrCollumn;
			}
			if (matrLine < SIZE && matrCollumn < SIZE)
			{
				minor[minorLine][minorCollumn] = matr[matrLine][matrCollumn];
			}
		}
	}
	return minor;
}

template<std::size_t MATR_SIZE>
SquareMatrix<MATR_SIZE>::MatrType<double, MATR_SIZE> SquareMatrix<MATR_SIZE>::GetAdjugate(const MatrType<double, MATR_SIZE> & matr) const
{
	MatrType<double, MATR_SIZE> adjugate = NULL_MATR;
	for (size_t i = 0; i < MATR_SIZE; ++i)
	{
		for (size_t j = 0; j < MATR_SIZE; ++j)
		{
			adjugate[i][j] = pow(-1, (i + j)) * CalcDet(GetMinor(matr, i, j));
		}
	}
	return GetTranspose(adjugate);
}

template<std::size_t MATR_SIZE>
SquareMatrix<MATR_SIZE>::MatrType<double, MATR_SIZE> SquareMatrix<MATR_SIZE>::GetTranspose(const MatrType<double, MATR_SIZE>& matr) const
{
	MatrType<double, MATR_SIZE> transpose = NULL_MATR;
	for (size_t i = 0; i < MATR_SIZE; ++i)
	{
		for (size_t j = 0; j < MATR_SIZE; ++j)
		{
			transpose[i][j] = matr[j][i];
		}
	}
	return transpose;
}

template<std::size_t MATR_SIZE>
SquareMatrix<MATR_SIZE>::MatrType<double, MATR_SIZE> SquareMatrix<MATR_SIZE>::GetInvert(const MatrType<double, MATR_SIZE>& matr) const
{
	const double det = CalcDet(matr);
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

template<std::size_t MATR_SIZE>
void SquareMatrix<MATR_SIZE>::WriteMatr(std::ostream & stream) const
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

template<std::size_t MATR_SIZE>
double SquareMatrix<MATR_SIZE>::GetDeterminant() const
{
	return CalcDet(m_matr);
}
