#include "pch.h"
#include "SwapEncryptor.h"

uint8_t swapBits(uint8_t byte)
{
	uint8_t part1 = (byte & 0b10000000) >> 2;
	uint8_t part2 = (byte & 0b00000111) << 2;
	uint8_t part3 = (byte & 0b01111000) >> 5 | (byte & 0b01111000) << 3;

	return part1 | part2 | part3;
}

uint8_t swapBitsBack(uint8_t byte)
{
	uint8_t part1 = (byte & 0b00100000) << 2;
	uint8_t part2 = (byte & 0b00011100) >> 2;
	uint8_t part3 = (byte & 0b11000011) << 5 | (byte & 0b11000011) >> 3;

	return part1 | part2 | part3;
}

uint8_t encodeByte(uint8_t byte, uint8_t key)
{
	byte ^= key;
	return swapBits(byte);
}

uint8_t decodeByte(uint8_t byte, uint8_t key)
{
	byte = swapBitsBack(byte);
	return byte ^ key;
}

void encode(const std::function<uint8_t(uint8_t, uint8_t)>& modeFunc, std::istream& input, std::ostream& output, uint8_t key)
{
	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), sizeof(byte)))
	{
		uint8_t encodedByte = modeFunc(byte, key);
		output.write(reinterpret_cast<char*>(&encodedByte), sizeof(encodedByte));
	}
}

void encryptStream(const std::string& mode, std::istream& input, std::ostream& output, uint8_t key)
{
	if (mode == "crypt")
	{
		encode(encodeByte, input, output, key);
	}
	else if (mode == "decrypt")
	{
		encode(decodeByte, input, output, key);
	}
	else
	{
		throw std::invalid_argument("Crypt mode must be \"crypt\" or \"decrypt\"");
	}
}
