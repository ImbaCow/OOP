#include "pch.h"
#include "Matrix.h"

SquareMatrix3::SquareMatrix3()
	:m_matr(MATR_SIZE, std::vector<double>(MATR_SIZE, 0))
{
}

void SquareMatrix3::InitFromFile(const std::string & inputFile)
{
	std::ifstream input(inputFile);
	if (!input.is_open())
	{
		throw std::invalid_argument("Input file not found");
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

void SquareMatrix3::SetMatrix(const MatrType<double> & matr)
{
	if (matr.size() != MATR_SIZE)
	{
		throw std::invalid_argument("Matrix must be square with size = " + std::to_string(MATR_SIZE));
	}
	for (size_t i = 0; i < matr.size(); ++i)
	{
		if (matr[i].size() != MATR_SIZE)
		{
			throw std::invalid_argument("Matrix must be square with size = " + std::to_string(MATR_SIZE));
		}
	}
	m_matr = matr;
}

void SquareMatrix3::WriteMainMatr()
{
	WriteMatr(m_matr);
}

void SquareMatrix3::WriteInvertMatr()
{
	WriteMatr(GetInvert(m_matr));
}

void SquareMatrix3::WriteAdjugateMatr()
{
	WriteMatr(GetAdjugate(m_matr));
}

void SquareMatrix3::WriteTransposeMatr()
{
	WriteMatr(GetTranspose(m_matr));
}

double SquareMatrix3::GetDet()
{
	return CalcDet(m_matr);
}

double SquareMatrix3::CalcDet(const MatrType<double> & matr)
{
	if (matr.size() == 1)
	{
		return matr[0][0];
	}
	double det = 0;
	for (size_t j = 0; j < matr.size(); ++j) 
	{
		det += pow((-1), j) * matr[0][j] * CalcDet(GetMinor(matr, 0, j));
	}
	return det;
}

SquareMatrix3::MatrType<double> SquareMatrix3::GetMinor(const MatrType<double> & matr, size_t i, size_t j)
{
	size_t minorSize = matr.size() - 1;
	if (!(i < matr.size() && j < matr.size()))
	{
		throw std::logic_error("Not correct line index in GetMinor!");
	}
	MatrType<double> minor(minorSize, std::vector<double>(minorSize, 0));
	for (size_t ti = 0, mi = 0; ti < matr.size(); ++ti, ++mi)
	{
		if (ti == i)
		{
			++ti;
		}
		for (size_t tj = 0, mj = 0; tj < matr.size(); ++tj, ++mj)
		{
			if (tj == j)
			{
				++tj;
			}
			if (ti < matr.size() && tj < matr.size())
			{
				minor[mi][mj] = matr[ti][tj];
			}
		}
	}
	return minor;
}

SquareMatrix3::MatrType<double> SquareMatrix3::GetAdjugate(const MatrType<double>& matr)
{
	MatrType<double> adjugate(matr.size(), std::vector<double>(matr.size(), 0));
	for (size_t i = 0; i < matr.size(); ++i)
	{
		for (size_t j = 0; j < matr.size(); ++j)
		{
			adjugate[i][j] = pow(-1, (i + j)) * CalcDet(GetMinor(matr, i, j));
		}
	}
	return GetTranspose(adjugate);
}

SquareMatrix3::MatrType<double> SquareMatrix3::GetTranspose(const MatrType<double>& matr)
{
	MatrType<double> transpose(matr.size(), std::vector<double>(matr.size(), 0));
	for (size_t i = 0; i < matr.size(); ++i)
	{
		for (size_t j = 0; j < matr.size(); ++j)
		{
			transpose[i][j] = matr[j][i];
		}
	}
	return transpose;
}

SquareMatrix3::MatrType<double> SquareMatrix3::GetInvert(const MatrType<double>& matr)
{
	double det = CalcDet(matr);
	if (det == 0)
	{
		throw std::logic_error("Unable to calculate inverse matrix, determinant is 0");
	}
	MatrType<double> invert = GetAdjugate(matr);
	for (auto & line : invert)
	{
		for (auto & value : line)
		{
			value /= det;
		}
	}
	return invert;
}

void SquareMatrix3::WriteMatr(const MatrType<double>& matr)
{
	std::cout << std::setprecision(3) << std::fixed;
	for (const auto & line : matr)
	{
		for (const auto & value : line)
		{
			std::cout << value << ' ';
		}
		std::cout << std::endl;
	}
}

