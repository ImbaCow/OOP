#pragma once

template <typename Type>
class CMyStringIterator
{
	friend class CMyString;

public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = Type;
	using difference_type = std::ptrdiff_t;
	using pointer = Type*;
	using reference = Type&;

	CMyStringIterator();
	CMyStringIterator(const CMyStringIterator& it);

	inline CMyStringIterator& operator=(const CMyStringIterator& it);
	inline CMyStringIterator& operator+=(difference_type offset);
	inline CMyStringIterator& operator-=(difference_type offset);
	inline Type& operator*() const;
	inline Type& operator[](difference_type offset) const;

	inline CMyStringIterator& operator++();
	inline CMyStringIterator& operator--();
	inline CMyStringIterator operator++(int);
	inline CMyStringIterator operator--(int);
	inline difference_type operator-(const CMyStringIterator& it) const;
	inline CMyStringIterator operator+(difference_type offset) const;
	inline CMyStringIterator operator-(difference_type offset) const;
	friend inline CMyStringIterator<Type> operator+(difference_type offset, const CMyStringIterator<Type>& it);

	inline bool operator==(const CMyStringIterator& it) const;
	inline bool operator!=(const CMyStringIterator& it) const;
	inline bool operator>(const CMyStringIterator& it) const;
	inline bool operator<(const CMyStringIterator& it) const;
	inline bool operator>=(const CMyStringIterator& it) const;
	inline bool operator<=(const CMyStringIterator& it) const;

private:
	Type* m_ch;

	CMyStringIterator(Type* ch);
};


template <typename Type>
inline CMyStringIterator<Type>::CMyStringIterator()
	: m_ch(nullptr)
{
}

template <typename Type>
inline CMyStringIterator<Type>::CMyStringIterator(Type* ptr)
	: m_ch(ptr)
{
}

template <typename Type>
inline CMyStringIterator<Type>::CMyStringIterator(const CMyStringIterator<Type>& it)
	: m_ch(it.m_ch)
{
}

template <typename Type>
inline CMyStringIterator<Type>& CMyStringIterator<Type>::operator=(const CMyStringIterator<Type>& it)
{
	m_ch = it.m_ch;
	return *this;
}

template <typename Type>
inline CMyStringIterator<Type>& CMyStringIterator<Type>::operator+=(difference_type offset)
{
	*this = *this + offset;
	return *this;
}

template <typename Type>
inline CMyStringIterator<Type>& CMyStringIterator<Type>::operator-=(difference_type offset)
{
	*this = *this - offset;
	return *this;
}

template <typename Type>
inline Type& CMyStringIterator<Type>::operator*() const
{
	return *m_ch;
}

template <typename Type>
inline Type& CMyStringIterator<Type>::operator[](difference_type offset) const
{
	return m_ch[offset];
}

template <typename Type>
inline CMyStringIterator<Type>& CMyStringIterator<Type>::operator++()
{
	++m_ch;
	return *this;
}

template <typename Type>
inline CMyStringIterator<Type>& CMyStringIterator<Type>::operator--()
{
	--m_ch;
	return *this;
}

template <typename Type>
inline CMyStringIterator<Type> CMyStringIterator<Type>::operator++(int)
{
	CMyStringIterator temp(*this);
	++m_ch;
	return temp;
}

template <typename Type>
inline CMyStringIterator<Type> CMyStringIterator<Type>::operator--(int)
{
	CMyStringIterator temp(*this);
	--m_ch;
	return temp;
}

template <typename Type>
inline typename CMyStringIterator<Type>::difference_type CMyStringIterator<Type>::operator-(const CMyStringIterator& it) const
{
	return m_ch - it.m_ch;
}

template <typename Type>
inline CMyStringIterator<Type> CMyStringIterator<Type>::operator+(difference_type offset) const
{
	return CMyStringIterator(m_ch + offset);
}

template <typename Type>
inline CMyStringIterator<Type> CMyStringIterator<Type>::operator-(difference_type offset) const
{
	return *this + (-offset);
}

template <typename Type>
inline CMyStringIterator<Type> operator+(typename CMyStringIterator<Type>::difference_type offset, const CMyStringIterator<Type>& it)
{
	return it + offset;
}

template <typename Type>
inline bool CMyStringIterator<Type>::operator==(const CMyStringIterator& it) const
{
	return m_ch == it.m_ch;
}

template <typename Type>
inline bool CMyStringIterator<Type>::operator!=(const CMyStringIterator& it) const
{
	return m_ch != it.m_ch;
}

template <typename Type>
inline bool CMyStringIterator<Type>::operator>(const CMyStringIterator& it) const
{
	return m_ch > it.m_ch;
}

template <typename Type>
inline bool CMyStringIterator<Type>::operator<(const CMyStringIterator& it) const
{
	return m_ch < it.m_ch;
}

template <typename Type>
inline bool CMyStringIterator<Type>::operator>=(const CMyStringIterator& it) const
{
	return m_ch >= it.m_ch;
}

template <typename Type>
inline bool CMyStringIterator<Type>::operator<=(const CMyStringIterator& it) const
{
	return m_ch <= it.m_ch;
}
