#pragma once

template <typename T>
class Matrix
{
private:
	size_t n = 0;
	size_t m = 0;
	vector<T> matrix;

public:
	Matrix();
	~Matrix();

	void Create(size_t  n, size_t  m);

};

