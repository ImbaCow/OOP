#include "pch.h"
#include "CTVSet.h"

void CTVSet::TurnOff()
{
	if (m_isTurnedOn)
	{
		m_prevChannel = m_currChannel;
		m_currChannel = 0;
		m_isTurnedOn = false;
		std::cout << "Tv is off" << std::endl;
	}
	else
	{
		throw std::logic_error("Tv is already off");
	}
}

void CTVSet::TurnOn()
{
	if (!m_isTurnedOn)
	{
		m_currChannel = m_prevChannel;
		m_isTurnedOn = true;
		std::cout << "Tv is on" << std::endl;
	}
	else
	{
		throw std::logic_error("Tv is already on");
	}
}

void CTVSet::SelectChannel(const unsigned channelNumber)
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("Tv is off");
	}
	if (channelNumber <= 0 || channelNumber >= MAX_CHANNEL_NUMBER)
	{
		throw std::invalid_argument("Channel out of range 1.." + std::to_string(MAX_CHANNEL_NUMBER - 1));
	}
	m_prevChannel = m_currChannel;
	m_currChannel = channelNumber;
	std::cout << "Channel " << channelNumber << " selected" << std::endl;

}

void CTVSet::SelectChannel(const std::string & name)
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("Tv is off");
	}
	const unsigned channelNumber = GetChannelByName(name);
	if (channelNumber)
	{
		m_prevChannel = m_currChannel;
		m_currChannel = channelNumber;
		std::cout << "Channel " << channelNumber << " selected" << std::endl;
	}
}

void CTVSet::SetChannelName(const unsigned channelNumber, const std::string & newName)
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("Tv is off");
	}
	if (channelNumber <= 0 || channelNumber >= MAX_CHANNEL_NUMBER)
	{
		throw std::invalid_argument("Channel out of range 1.." + std::to_string(MAX_CHANNEL_NUMBER - 1));
	}
	if (newName.empty())
	{
		throw std::invalid_argument("String can't be empty");
	}
	std::string validNewName(newName);
	Channel::FormatName(validNewName);
	if (validNewName.empty())
	{
		throw std::invalid_argument("String must have at least 1 non-space symbol");
	}
	for (auto & channel : m_channels)
	{
		if (channel.GetName() == validNewName)
		{
			channel.SetName(m_channels[channelNumber].GetName());
		}
	}
	m_channels[channelNumber].SetName(newName);
	std::cout << "Channel name '" << validNewName << "' for " << channelNumber << " channel selected" << std::endl;
}

void CTVSet::DeleteChannelName(const std::string & removableName)
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("Tv is off");
	}
	const unsigned channelNumber = GetChannelByName(removableName);
	if (channelNumber)
	{
		m_channels[channelNumber].RemoveName();
		std::cout << "Channel name '" << removableName << "' deleted from " << channelNumber << " channel" << std::endl;
	}
}

std::string CTVSet::GetChannelName(const unsigned channelNumber) const
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("Tv is off");
	}
	if (channelNumber <= 0 && channelNumber >= MAX_CHANNEL_NUMBER)
	{
		throw std::invalid_argument("Channel out of range 1.." + std::to_string(MAX_CHANNEL_NUMBER - 1));
	}
	return m_channels[channelNumber].GetName();
}

unsigned CTVSet::GetChannelByName(const std::string & name) const
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("Tv is off");
	}
	if (name.empty())
	{
		throw std::invalid_argument("String can't be empty");
	}

	const auto it = std::find_if(m_channels.begin(), m_channels.end(), [&name](const auto channel) {
		return (channel.GetName() == name);
	});
	if (m_channels.end() != it)
	{
		return std::distance(m_channels.begin(), it);
	}
	throw std::invalid_argument("Channel '" + name + "' not found");
}

void CTVSet::SelectPreviousChannel()
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("Tv is off");
	}
	if (m_prevChannel)
	{
		const unsigned temp = m_currChannel;
		m_currChannel = m_prevChannel;
		m_prevChannel = temp;
	}
	std::cout << "Previous " << m_currChannel << " Channel selected" << std::endl;
}

void CTVSet::Info() const
{
	const std::string state = m_isTurnedOn ? "on" : "off";
	std::cout << "Tv is " << state << std::endl;
	std::cout << "Current channel: " << m_currChannel << std::endl;
	for (unsigned i = 1; i < MAX_CHANNEL_NUMBER; ++i)
	{
		if (!m_channels[i].HasEmptyName())
		{
			std::cout << i << " - " << m_channels[i].GetName() << std::endl;
		}
	}
}

unsigned CTVSet::GetCurrChannel() const
{
	return m_currChannel;
}

std::string CTVSet::GetCurrChannelName() const
{
	return m_channels[m_currChannel].GetName();
}
