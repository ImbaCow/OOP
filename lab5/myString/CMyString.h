#pragma once
#include "CMyStringIterator.h"

class CMyString
{
public:
	using iterator = CMyStringIterator<char>;
	using const_iterator = CMyStringIterator<const char>;
		
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	CMyString(const char* pString = "");
	CMyString(const char* pString, size_t size);
	CMyString(const CMyString& other);
	CMyString(CMyString&& other);
	CMyString(const std::string& stlString);
	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	friend CMyString operator+(const CMyString& a, const CMyString& b);
	CMyString& operator+=(const CMyString& b);
	CMyString& operator=(const CMyString& b);
	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

	template <typename T>
	static CMyStringIterator<const T> GetConstIterator(CMyStringIterator<T> it);

private:
	char* m_string;
	size_t m_size;

	CMyString(size_t size);
};

bool operator==(const CMyString& a, const CMyString& b);
bool operator!=(const CMyString& a, const CMyString& b);

bool operator<(const CMyString& a, const CMyString& b);
bool operator>(const CMyString& a, const CMyString& b);

bool operator<=(const CMyString& a, const CMyString& b);
bool operator>=(const CMyString& a, const CMyString& b);

std::ostream& operator<<(std::ostream& out, const CMyString& b);
//std::istream& operator>>(std::istream& in, CMyString& b);

template <typename T>
inline CMyStringIterator<const T> CMyString::GetConstIterator(CMyStringIterator<T> it)
{
	return CMyStringIterator<const T>(it.m_ch);
}
