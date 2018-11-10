#pragma once
class Channel
{
public:
	void SetName(const std::string & name);
	void RemoveName();
	std::string GetName() const;
	bool HasEmptyName() const;

	static void FormatName(std::string & str);
private:
	std::string m_name;
};

