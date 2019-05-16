#include "pch.h"
#include "CMyString.h"

int CompareStrings(const CMyString& a, const CMyString& b)
{
	size_t aLen = a.GetLength();
	size_t bLen = b.GetLength();

	int result = memcmp(a.GetStringData(), b.GetStringData(), std::min(aLen, bLen));
	return (result == 0) ? (aLen - bLen) : result;
}

CMyString::CMyString(const char* pString, size_t size)
{
	m_string = new char[size + 1];
	memcpy(m_string, pString, size);
	m_string[size] = '\0';
	m_size = size;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.m_string, other.m_size)
{
}

CMyString::CMyString(CMyString&& other)
{
	m_string = std::move(other.m_string);
	m_size = std::move(other.m_size);
	other.m_string = nullptr;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	delete[] m_string;
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_string;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_size)
	{
		throw std::invalid_argument("start position out of range");
	}
	return CMyString(m_string + start, std::min(m_size - start, length));
}

void CMyString::Clear()
{
	delete[] m_string;
	m_string = new char[1]{ "" };
	m_size = 0;
}

CMyString& CMyString::operator+=(const CMyString& b)
{
	*this = *this + b;
	return *this;
}

CMyString& CMyString::operator=(const CMyString& b)
{
	if (this != &b)
	{
		CMyString temp(b);

		std::swap(m_string, temp.m_string);
		std::swap(m_size, temp.m_size);
	}

	return *this;
}

char& CMyString::operator[](size_t index) const
{
	return m_string[index];
}

CMyString operator+(const CMyString& a, const CMyString& b)
{
	CMyString result(a);
	result.Append(b);

	return result;
}

void CMyString::Append(const CMyString& str)
{
	size_t strLen = str.GetLength();

	size_t newStrSize = m_size + strLen;
	char* newStr = new char[newStrSize + 1];

	memcpy(newStr, m_string, m_size);
	memcpy(newStr + m_size, str.GetStringData(), strLen + 1);
	delete[] m_string;

	m_string = newStr;
	m_size = newStrSize;
}

CMyString::iterator CMyString::begin()
{
	return iterator(m_string);
}

CMyString::iterator CMyString::end()
{
	return iterator(m_string + m_size);
}

CMyString::reverse_iterator CMyString::rbegin()
{
	return reverse_iterator(end());
}

CMyString::reverse_iterator CMyString::rend()
{
	return reverse_iterator(begin());
}

CMyString::const_iterator CMyString::begin() const
{
	return const_iterator(m_string);
}

CMyString::const_iterator CMyString::end() const
{
	return const_iterator(m_string + m_size);
}

CMyString::const_reverse_iterator CMyString::rbegin() const
{
	return const_reverse_iterator(end());
}

CMyString::const_reverse_iterator CMyString::rend() const
{
	return const_reverse_iterator(begin());
}

bool operator==(const CMyString& a, const CMyString& b)
{
	return CompareStrings(a, b) == 0;
}

bool operator!=(const CMyString& a, const CMyString& b)
{
	return !(a == b);
}

bool operator<(const CMyString& a, const CMyString& b)
{
	return CompareStrings(a, b) < 0;
}

bool operator>(const CMyString& a, const CMyString& b)
{
	return CompareStrings(a, b) > 0;
}

bool operator<=(const CMyString& a, const CMyString& b)
{
	return !(CompareStrings(a, b) > 0);
}

bool operator>=(const CMyString& a, const CMyString& b)
{
	return !(CompareStrings(a, b) < 0);
}

std::ostream& operator<<(std::ostream& out, const CMyString& b)
{
	for (size_t i = 0; i < b.GetLength(); i++)
	{
		out << b[i];
	}
	return out;
}
