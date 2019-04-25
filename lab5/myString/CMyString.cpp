#include "pch.h"
#include "CMyString.h"

int CompareStrings(const CMyString& a, const CMyString& b)
{
	size_t aLen = a.GetLength();
	size_t bLen = b.GetLength();

	return memcmp(a.GetStringData(), b.GetStringData(), std::min(aLen, bLen));
}

CMyString::CMyString(const char* pString, size_t size)
{
	m_string = new char[size + 1];
	memcpy(m_string, pString, size + 1);
	m_size = std::move(size);
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
	m_string = other.m_string;
	m_size = other.m_size;
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

char& CMyString::operator[](size_t index)
{
	return m_string[index];
}

CMyString operator+(const CMyString& a, const CMyString& b)
{
	size_t aLen = a.GetLength();
	size_t bLen = b.GetLength();

	char* resultStr = new char[aLen + bLen + 1];

	memcpy(resultStr, a.GetStringData(), aLen);
	memcpy(resultStr + aLen, b.GetStringData(), bLen + 1);

	return CMyString(resultStr, aLen + bLen);
}

bool operator==(const CMyString& a, const CMyString& b)
{
	return (CompareStrings(a, b) == 0);
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
	return (a < b) || (a == b);
}

bool operator>=(const CMyString& a, const CMyString& b)
{
	return (a > b) || (a == b);
}

std::ostream& operator<<(std::ostream& out, const CMyString& b)
{
	out << b.GetStringData();
	return out;
}
