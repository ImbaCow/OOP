#pragma once

class MyArray
{
public:
	void AddItemsFromString(const std::string & input);
	void ProcessArray(); // 6. Multiply each element of the array by the maximum element of the original array and divide by the minimum element of the original array
	void SortArray();
	std::string ReturnByString();
private:
	const unsigned ROUNDING_DEGREE = 3;
	std::vector<double> m_array;
};
