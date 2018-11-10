#include "pch.h"
#include "MyArray.h"

void MyArray::AddItemsFromString(const std::string & input)
{
	std::stringstream sstream(input);
	double item;
	while (sstream >> item)
	{
		m_array.push_back(item);
	}
}

void MyArray::ProcessArray()
{
	if (m_array.empty())
	{
		throw std::logic_error("Array is empty");
	}
	auto minMax = std::minmax_element(m_array.begin(), m_array.end());
	double min = *minMax.first;
	double max = *minMax.second;

	std::transform(m_array.begin(), m_array.end(), m_array.begin(), [&min, &max](auto item) {
		return item * max / min;
	});
}

void MyArray::SortArray()
{
	std::sort(m_array.begin(), m_array.end());
}

std::string MyArray::ReturnByString()
{
	if (m_array.empty())
	{
		return std::string();
	}
	std::stringstream result;
	result.precision(ROUNDING_DEGREE);
	result << std::fixed;
	std::copy(m_array.begin(), m_array.end() - 1, std::ostream_iterator<double>(result, " "));
	result << *m_array.rbegin();	
	return result.str();
}
