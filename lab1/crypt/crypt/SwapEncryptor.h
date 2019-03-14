#pragma once

uint8_t SwapBits(uint8_t byte);
uint8_t SwapBitsBack(uint8_t byte);

uint8_t EncodeByte(uint8_t byte, uint8_t key);
uint8_t DecodeByte(uint8_t byte, uint8_t key);

void EncryptStream(const std::string& mode, std::istream& input, std::ostream& outpit, uint8_t key);
