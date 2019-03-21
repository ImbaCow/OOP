#pragma once

std::map<std::string, size_t> CreateWordsMap(std::istream& input);
std::string WordsMapToString(const std::map<std::string, size_t>& wordsMap);
