#pragma once
#include "CMyArrayIterator.h"

template <typename T>
class CMyArray
{
public:

	using iterator = CMyArrayIterator<T>;
	using const_iterator = CMyArrayIterator<const T>;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	CMyArray(const T* pString, size_t size);
	CMyArray(const CMyArray& other);
	CMyArray(CMyArray&& other);
	CMyArray();
	~CMyArray();

	size_t GetSize() const;
	void Clear();

	void Push(const T& item);
	void Resize(size_t size);

	void operator=(const CMyArray& other);
	void operator=(CMyArray&& other);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

private:
	T* m_arr = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;

	CMyArray(size_t size);
	CMyArray(T* arr, size_t size, size_t capacity);
};
