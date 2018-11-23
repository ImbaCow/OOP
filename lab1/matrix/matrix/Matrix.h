#pragma once

class SquareMatrix3
{
public:
	static const size_t MATR_SIZE = 3;

	SquareMatrix3() {};
	SquareMatrix3(const std::string & inputFile);
	SquareMatrix3(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE> & matr);

	void InitFromFile(const std::string & inputFile);
	void InitFromMatr(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE> & matr);

	SquareMatrix3 * Invert();
	SquareMatrix3 * FindAdjugate();
	SquareMatrix3 * Transpose();

	void WriteMatr(std::ostream & stream);
	double GetDeterminant();
private:
	template<typename T, std::size_t SIZE>
	using MatrType = std::array<std::array<T, SIZE>, SIZE>;

	static const size_t PRECISION = 3;
	MatrType<double, MATR_SIZE> m_matr = { {0} };

	template <std::size_t SIZE>
	double CalcDet(const MatrType<double, SIZE> & matr) const;

	template <std::size_t SIZE>
	MatrType<double, SIZE - 1> GetMinor(const MatrType<double, SIZE> & matr, size_t i, size_t j) const;

	MatrType<double, MATR_SIZE> GetAdjugate(const MatrType<double, MATR_SIZE> & matr) const;
	MatrType<double, MATR_SIZE> GetTranspose(const MatrType<double, MATR_SIZE> & matr) const;
	MatrType<double, MATR_SIZE> GetInvert(const MatrType<double, MATR_SIZE> & matr) const;
};

