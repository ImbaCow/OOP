#pragma once

class SquareMatrix3
{
public:
	template<typename T>
	using MatrType = std::vector<std::vector<T>>;

	SquareMatrix3();
	void InitFromFile(const std::string & inputFile);
	void SetMatrix(const MatrType<double> & matr);

	void WriteMainMatr();
	void WriteInvertMatr();
	void WriteAdjugateMatr();
	void WriteTransposeMatr();

	double GetDet();
private:
	static const size_t MATR_SIZE = 3;
	MatrType<double> m_matr;

	double CalcDet(const MatrType<double> & matr);

	MatrType<double> GetMinor(const MatrType<double> & matr, size_t i, size_t j);
	MatrType<double> GetAdjugate(const MatrType<double> & matr);
	MatrType<double> GetTranspose(const MatrType<double> & matr);
	MatrType<double> GetInvert(const MatrType<double> & matr);

	void WriteMatr(const MatrType<double> & matr);
};

