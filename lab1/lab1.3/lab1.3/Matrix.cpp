#include "Matrix.h"



Matrix::Matrix()
{
}


Matrix::~Matrix()
{
}

template<typename T>
void Matrix<T>::Create(size_t n, size_t  m)
{
	matrix.reserve(n * m);
}
