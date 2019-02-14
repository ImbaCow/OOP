#pragma once

template<std::size_t MATR_SIZE>
class SquareMatrix
{
public:
	SquareMatrix();
	SquareMatrix(const std::string & inputFile);
	SquareMatrix(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE> & matr);

	void SetFromFile(const std::string & inputFile);
	void SetFromMatr(const std::array<std::array<double, MATR_SIZE>, MATR_SIZE> & matr);

	void Invert();
	void Adjugate();
	void Transpose();

	void WriteMatr(std::ostream & stream) const;
	double GetDeterminant() const;
private:
	template<typename T, std::size_t SIZE>
	using MatrType = std::array<std::array<T, SIZE>, SIZE>;

	const MatrType<double, MATR_SIZE> NULL_MATR = { {0} };
	MatrType<double, MATR_SIZE> m_matr;

	template <std::size_t SIZE>
	double CalcDet(const MatrType<double, SIZE> & matr) const;

	template <std::size_t SIZE>
	MatrType<double, SIZE - 1> GetMinor(const MatrType<double, SIZE> & matr, size_t line, size_t collumn) const;

	MatrType<double, MATR_SIZE> GetAdjugate(const MatrType<double, MATR_SIZE> & matr) const;
	MatrType<double, MATR_SIZE> GetTranspose(const MatrType<double, MATR_SIZE> & matr) const;
	MatrType<double, MATR_SIZE> GetInvert(const MatrType<double, MATR_SIZE> & matr) const;
};

