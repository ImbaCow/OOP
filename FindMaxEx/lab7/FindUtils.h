#pragma once
#include "pch.h"

template <typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, Less const& less);

template <typename T>
bool FindMax(const std::vector<T>& arr, T& maxValue);

template <>
bool FindMax<const char*>(const std::vector<const char*>& arr, const char*& maxValue);

template <typename T>
using vectorIterator = typename std::vector<T>::const_iterator;

template <typename T, typename Less>
vectorIterator<T> MaxElement(vectorIterator<T> first, vectorIterator<T> last, const Less& less)
{
	if (first == last)
	{
		return last;
	}
	vectorIterator<T> max = first;
	++first;

	for (; first != last; ++first)
	{
		if (less(*max, *first))
		{
			max = first;
		}
	}
	return max;
}

template <typename T>
bool FindMax(const std::vector<T>& arr, T& maxValue)
{
	return FindMax(arr, maxValue, std::less);
}

bool lessCharPtr(const char* first, const char* second)
{
	return (*first < *second);
}


template <>
bool FindMax<const char*>(const std::vector<const char*>& arr, const char*& maxValue)
{
	return FindMax(arr, maxValue, lessCharPtr);
}

template <typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	auto maxIter = MaxElement<T>(arr.begin(), arr.end(), less);
	if (maxIter == arr.end())
	{
		return false;
	}

	maxValue = *maxIter;
	return true;
}