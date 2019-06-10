#include "pch.h"
#include "CMyArray.h"

const int CAPACITY_PUSH_STEP = 5;
const int EMPTY_CAPACITY_SIZE = 1;

template <typename T>
CMyArray<T>::CMyArray(size_t size)
	: m_size(size)
{
	m_arr = static_cast<T*>(malloc(size * sizeof(T)));
	if (m_arr == nullptr)
	{
		throw std::bad_alloc();
	}
}

template <typename T>
CMyArray<T>::CMyArray(T* arr, size_t size, size_t capacity)
	: CMyArray(capacity)
{
	m_size = size;
	CMyArrayIterator<T> currPtr(m_arr);
	CMyArrayIterator<T> endPtr(arr + size);
	try
	{
		for (CMyArrayIterator<T> otherPtr(arr); otherPtr != endPtr; ++currPtr, ++otherPtr)
		{
			new (currPtr.m_item) T(*otherPtr);
		}
	}
	catch (...)
	{
		DestroyArr(m_arr, currPtr.m_item);
	}
}

template <typename T>
void CMyArray<T>::DestroyArr(T* begin, T* end)
{
	while (begin != end)
	{
		--end;
		end->~T();
	}
	free(end);
}

template <typename T>
CMyArray<T>::CMyArray(T* arr, size_t size)
	: CMyArray(arr, size, size)
{
}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& other)
	: CMyArray(other.m_arr, other.m_size)
{
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray&& other)
{
	m_arr = std::move(other.m_arr);
	m_size = std::move(other.size);
	m_capacity = std::move(other.m_capacity);
	m_arr = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
CMyArray<T>::CMyArray()
	: CMyArray(EMPTY_CAPACITY_SIZE)
{
	m_size = 0;
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	DestroyArr(begin().m_item, end().m_item);
}

template <typename T>
size_t CMyArray<T>::GetSize() const
{
	return m_size;
}

template <typename T>
void CMyArray<T>::Clear()
{
	CMyArray temp;
	std::swap(m_arr, temp.m_arr);
	std::swap(m_size, temp.m_size);
	std::swap(m_capacity, temp.m_capacity);
}

template <typename T>
void CMyArray<T>::Push(const T& item)
{
	if (m_size < m_capacity)
	{
		m_arr[m_size] = item;
		++m_size;
	}
	else
	{
		CMyArray temp(m_arr, m_size, m_capacity + CAPACITY_PUSH_STEP);
		std::swap(m_arr, temp.m_arr);
		std::swap(m_size, temp.m_size);
		std::swap(m_capacity, temp.m_capacity);

		m_arr[m_size] = item;
		++m_size;
	}
}

template <typename T>
void CMyArray<T>::Resize(size_t size)
{
	if (size <= m_capacity)
	{
		m_size = size;
	}
	else
	{
		size_t oldSize = m_size;
		*this = CMyArray(m_arr, size, size);
		for (size_t offset = oldSize; offset < size; ++offset)
		{
			m_arr[offset] = T();
		}
	}
}

template <typename T>
void CMyArray<T>::operator=(const CMyArray& other)
{
	if (other.m_size <= m_capacity)
	{
		memcpy(m_arr, other.m_arr, other.m_size);
		m_size = other.m_size;
	}
	else
	{
		CMyArray temp(other);
		std::swap(m_arr, temp.m_arr);
		std::swap(m_size, temp.m_size);
		std::swap(m_capacity, temp.m_capacity);
	}
}

template <typename T>
void CMyArray<T>::operator=(CMyArray&& other)
{
	if (other.m_size <= m_capacity)
	{
		memcpy(m_arr, other.m_arr, other.m_size);
		m_size = other.m_size;
	}
	else
	{
		CMyArray temp(other);
		std::swap(m_arr, temp.m_arr);
		std::swap(m_size, temp.m_size);
		std::swap(m_capacity, temp.m_capacity);
	}
}

template <typename T>
T& CMyArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Out of range.");
	}
	return m_arr[index];
}

template <typename T>
const T& CMyArray<T>::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Out of range.");
	}
	return m_arr[index];
}

template <typename T>
typename CMyArray<T>::iterator CMyArray<T>::begin()
{
	return iterator(m_arr);
}

template <typename T>
typename CMyArray<T>::iterator CMyArray<T>::end()
{
	return iterator(m_arr + m_size);
}

template <typename T>
typename CMyArray<T>::const_iterator CMyArray<T>::begin() const
{
	return iterator(m_arr);
}

template <typename T>
typename CMyArray<T>::const_iterator CMyArray<T>::end() const
{
	return iterator(m_arr + m_size);
}

template <typename T>
typename CMyArray<T>::reverse_iterator CMyArray<T>::rbegin()
{
	return reverse_iterator(end());
}

template <typename T>
typename CMyArray<T>::reverse_iterator CMyArray<T>::rend()
{
	return reverse_iterator(begin());
}

template <typename T>
typename CMyArray<T>::const_reverse_iterator CMyArray<T>::rbegin() const
{
	return reverse_iterator(end());
}

template <typename T>
typename CMyArray<T>::const_reverse_iterator CMyArray<T>::rend() const
{
	return reverse_iterator(begin());
}
