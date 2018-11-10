#pragma once
#include "Channel.h"

class CTVSet
{
public:
	void TurnOff();
	void TurnOn();

	void SelectChannel(unsigned number);
	void SelectChannel(const std::string & name);

	void SetChannelName(unsigned channelNumber, const std::string & newName);
	void DeleteChannelName(const std::string & newName);

	std::string GetChannelName(unsigned number) const;
	unsigned GetChannelByName(const std::string & name) const;
	void SelectPreviousChannel();
	void Info() const;
	unsigned GetCurrChannel() const;
	std::string GetCurrChannelName() const;
protected:
	static const unsigned MAX_CHANNEL_NUMBER = 100;

	bool m_isTurnedOn = false;
	std::array<Channel, MAX_CHANNEL_NUMBER> m_channels;
	unsigned m_currChannel = 0;
	unsigned m_prevChannel = 1;
};
