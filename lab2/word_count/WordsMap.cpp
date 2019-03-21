#include "pch.h"
#include "WordsMap.h"

void ToUpper(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

std::map<std::string, size_t> CreateWordsMap(std::istream& input)
{
	std::map<std::string, size_t> wordsMap;
	std::string word;
	while (input >> word)
	{
		ToUpper(word);
		if (wordsMap.count(word))
		{
			++wordsMap[word];
		}
		else
		{
			wordsMap[word] = 1;
		}
	}

	return wordsMap;
}

std::string WordsMapToString(const std::map<std::string, size_t>& wordsMap)
{
	std::string resultStr;
	for (const auto& word : wordsMap)
	{
		resultStr += word.first + " - " + std::to_string(word.second) + '\n';
	}

	return resultStr;
}
