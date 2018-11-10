#pragma once
#include <string>
#include <cstdint>

uint8_t GetInputByte(const char * input)
{
	int number = std::stoi(input);
	if (number < 0 && number >= 256)
	{
		throw std::invalid_argument("Number out of range [0..255]");
	}
	return static_cast<uint8_t>(number);
}

uint8_t GetFlipedByte(uint8_t byte)
{
	uint8_t result = 0;
	for (size_t i = 0; i < 8; ++i)
	{
		if (byte & (1 << (7 - i)))
		{
			result += 1 << i;
		}
	}
	return result;
}