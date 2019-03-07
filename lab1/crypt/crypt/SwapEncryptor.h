#pragma once

uint8_t swapBits(uint8_t byte);
uint8_t swapBitsBack(uint8_t byte);

uint8_t encodeByte(uint8_t byte, uint8_t key);
uint8_t decodeByte(uint8_t byte, uint8_t key);

class SwapEncryptor
{
public:
	SwapEncryptor(uint8_t key = 0);

	void encryptStream(const std::string& mode, std::istream& input, std::ostream& outpit);

private:
	uint8_t m_key;

	void encode(std::istream& input, std::ostream& output, const std::function<uint8_t(uint8_t, uint8_t)>& modeFunc);
};
