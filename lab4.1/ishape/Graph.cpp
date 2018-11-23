#include "pch.h"
#include "Graph.h"

void Graph::InitFromFile(const std::string & file_name)
{
	std::ifstream input(file_name);
	if (!input.is_open())
	{
		throw std::invalid_argument("Input file not found");
	}
	std::string input_line;
	while (input >> input_line)
	{
		City city;
		city.isMain
		m_cities.push_back
	}
}
