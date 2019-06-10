#pragma once
#include "pch.h"

struct Human
{
	std::string fio;
	size_t height;
	size_t weight;

	static bool lessHumanHeight(const Human& first, const Human& second)
	{
		return first.height < second.height;
	}

	static bool lessHumanWeight(const Human& first, const Human& second)
	{
		return first.weight < second.weight;
	}
};

bool operator==(const Human& first, const Human& second)
{
	return first.fio == second.fio && first.height == second.height && first.weight == second.weight;
}

std::ostream& operator<<(std::ostream& out, const Human& human)
{
	out << "{" << human.fio << ", " << human.height << ", " << human.weight << "}" << std::endl;
	return out;
}