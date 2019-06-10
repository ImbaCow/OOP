#pragma once

template <typename T>
class CMyArray;

template <typename T>
class CMyArrayIterator
{
	friend class CMyArray<T>;

public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	CMyArrayIterator();
	CMyArrayIterator(const CMyArrayIterator& it);

	inline CMyArrayIterator& operator=(const CMyArrayIterator& it);
	inline CMyArrayIterator& operator+=(difference_type offset);
	inline CMyArrayIterator& operator-=(difference_type offset);
	inline T& operator*() const;
	inline T& operator[](difference_type offset) const;

	inline CMyArrayIterator& operator++();
	inline CMyArrayIterator& operator--();
	inline CMyArrayIterator operator++(int);
	inline CMyArrayIterator operator--(int);
	inline difference_type operator-(const CMyArrayIterator& it) const;
	inline CMyArrayIterator operator+(difference_type offset) const;
	inline CMyArrayIterator operator-(difference_type offset) const;
	friend inline CMyArrayIterator<T> operator+(difference_type offset, const CMyArrayIterator<T>& it);

	inline bool operator==(const CMyArrayIterator& it) const;
	inline bool operator!=(const CMyArrayIterator& it) const;
	inline bool operator>(const CMyArrayIterator& it) const;
	inline bool operator<(const CMyArrayIterator& it) const;
	inline bool operator>=(const CMyArrayIterator& it) const;
	inline bool operator<=(const CMyArrayIterator& it) const;

private:
	T* m_item = nullptr;

	CMyArrayIterator(T* ch);
};

template <typename T>
inline CMyArrayIterator<T>::CMyArrayIterator()
	: m_item(nullptr)
{
}

template <typename T>
inline CMyArrayIterator<T>::CMyArrayIterator(T* ptr)
	: m_item(ptr)
{
}

template <typename T>
inline CMyArrayIterator<T>::CMyArrayIterator(const CMyArrayIterator<T>& it)
	: m_item(it.m_item)
{
}

template <typename T>
inline CMyArrayIterator<T>& CMyArrayIterator<T>::operator=(const CMyArrayIterator<T>& it)
{
	m_item = it.m_item;
	return *this;
}

template <typename T>
inline CMyArrayIterator<T>& CMyArrayIterator<T>::operator+=(difference_type offset)
{
	*this = *this + offset;
	return *this;
}

template <typename T>
inline CMyArrayIterator<T>& CMyArrayIterator<T>::operator-=(difference_type offset)
{
	*this = *this - offset;
	return *this;
}

template <typename T>
inline T& CMyArrayIterator<T>::operator*() const
{
	return *m_item;
}

template <typename T>
inline T& CMyArrayIterator<T>::operator[](difference_type offset) const
{
	return m_item[offset];
}

template <typename T>
inline CMyArrayIterator<T>& CMyArrayIterator<T>::operator++()
{
	++m_item;
	return *this;
}

template <typename T>
inline CMyArrayIterator<T>& CMyArrayIterator<T>::operator--()
{
	--m_item;
	return *this;
}

template <typename T>
inline CMyArrayIterator<T> CMyArrayIterator<T>::operator++(int)
{
	CMyArrayIterator temp(*this);
	++m_item;
	return temp;
}

template <typename T>
inline CMyArrayIterator<T> CMyArrayIterator<T>::operator--(int)
{
	CMyArrayIterator temp(*this);
	--m_item;
	return temp;
}

template <typename T>
inline typename CMyArrayIterator<T>::difference_type CMyArrayIterator<T>::operator-(const CMyArrayIterator& it) const
{
	return m_item - it.m_item;
}

template <typename T>
inline CMyArrayIterator<T> CMyArrayIterator<T>::operator+(difference_type offset) const
{
	return CMyArrayIterator(m_item + offset);
}

template <typename T>
inline CMyArrayIterator<T> CMyArrayIterator<T>::operator-(difference_type offset) const
{
	return *this + (-offset);
}

template <typename T>
inline CMyArrayIterator<T> operator+(typename CMyArrayIterator<T>::difference_type offset, const CMyArrayIterator<T>& it)
{
	return it + offset;
}

template <typename T>
inline bool CMyArrayIterator<T>::operator==(const CMyArrayIterator& it) const
{
	return m_item == it.m_item;
}

template <typename T>
inline bool CMyArrayIterator<T>::operator!=(const CMyArrayIterator& it) const
{
	return m_item != it.m_item;
}

template <typename T>
inline bool CMyArrayIterator<T>::operator>(const CMyArrayIterator& it) const
{
	return m_item > it.m_item;
}

template <typename T>
inline bool CMyArrayIterator<T>::operator<(const CMyArrayIterator& it) const
{
	return m_item < it.m_item;
}

template <typename T>
inline bool CMyArrayIterator<T>::operator>=(const CMyArrayIterator& it) const
{
	return m_item >= it.m_item;
}

template <typename T>
inline bool CMyArrayIterator<T>::operator<=(const CMyArrayIterator& it) const
{
	return m_item <= it.m_item;
}
