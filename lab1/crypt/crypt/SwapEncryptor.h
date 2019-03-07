#pragma once

uint8_t swapBits(uint8_t byte);
uint8_t swapBitsBack(uint8_t byte);

uint8_t encodeByte(uint8_t byte, uint8_t key);
uint8_t decodeByte(uint8_t byte, uint8_t key);

void encryptStream(const std::string& mode, std::istream& input, std::ostream& outpit, uint8_t key);
