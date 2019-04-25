#pragma once
class CMyString
{
public:
	CMyString(const char* pString = "");
	CMyString(const char* pString, size_t length);
	CMyString(const CMyString& other);
	CMyString(CMyString&& other);
	CMyString(const std::string& stlString);
	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator+=(const CMyString& b);
	CMyString& operator=(const CMyString& b);
	char& operator[](size_t index);

private:
	char* m_string;
	size_t m_size;
};

CMyString operator+(const CMyString& a, const CMyString& b);

bool operator==(const CMyString& a, const CMyString& b);
bool operator!=(const CMyString& a, const CMyString& b);

bool operator<(const CMyString& a, const CMyString& b);
bool operator>(const CMyString& a, const CMyString& b);

bool operator<=(const CMyString& a, const CMyString& b);
bool operator>=(const CMyString& a, const CMyString& b);

std::ostream& operator<<(std::ostream& out, const CMyString& b);
//std::istream& operator>>(std::istream& in, CMyString& b);

int CompareStrings(const CMyString& a, const CMyString& b);