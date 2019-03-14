#pragma once
#include "pch.h"
#include "PrimeNumberUtils.h"

inline std::vector<bool> GeneratePrimesBoolVector(int upperBound)
{
	int arrSize = upperBound + 1;
	int sizeSqrt = static_cast<int>(sqrt(arrSize));
	std::vector<bool> boolVector(arrSize, true);

	for (int i = 3; i <= sizeSqrt; i += 2)
	{
		if (boolVector[i])
		{
			for (int j = 3; i * j < arrSize; j += 2)
			{
				boolVector[i * j] = false;
			}
		}
	}

	return boolVector;
}

inline std::set<int> FromBoolVectorToPrimeSet(const std::vector<bool>& boolVector)
{
	std::set<int> primeSet{ 2 };
	for (size_t i = 3; i < boolVector.size(); i += 2)
	{
		if (boolVector[i])
		{
			primeSet.insert(i);
		}
	}

	return primeSet;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
	{
		return std::set<int>();
	}
	if (upperBound > MAX_UPPER_BOUND)
	{
		throw std::invalid_argument("Given number is too high");
	}

	std::vector<bool> boolVector = GeneratePrimesBoolVector(upperBound);
	std::set<int> primeSet = FromBoolVectorToPrimeSet(boolVector);

	return primeSet;
}

std::string IntSetToString(const std::set<int>& primeSet)
{
	std::string resultString;

	auto itBegin = std::begin(primeSet);
	auto itEnd = std::end(primeSet);

	if (itBegin != itEnd)
	{
		resultString += std::to_string(*itBegin);
		++itBegin;
	}

	for (; itBegin != itEnd; ++itBegin)
	{
		resultString += ' ' + std::to_string(*itBegin);
	}
	return resultString;
}
