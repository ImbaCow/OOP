#include "pch.h"
#include <boost/algorithm/string/trim_all.hpp>
#include "Channel.h"

void Channel::SetName(const std::string & newName)
{
	std::string validatedName(newName);
	FormatName(validatedName);
	m_name = validatedName;
}

void Channel::RemoveName()
{
	m_name.clear();
}

std::string Channel::GetName() const
{
	return m_name;
}

bool Channel::HasEmptyName() const
{
	return m_name.empty();
}

void Channel::FormatName(std::string & str)
{
	boost::trim_all(str);
}
