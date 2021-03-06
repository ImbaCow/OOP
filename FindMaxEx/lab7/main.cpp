#pragma once
#include "pch.h"
#include "Human.h"
#include "FindUtils.h"

int main()
{
	std::vector<Human> humanArr{
		{ "common human name", 160, 60 },
		{ "common2 human2 name2", 180, 70 },
		{ "common3 human3 name3", 170, 80 }
	};

	Human maxHuman;
	FindMax<Human>(humanArr, maxHuman, Human::lessHumanWeight);
	std::cout << "Max weight: " << maxHuman;
	FindMax<Human>(humanArr, maxHuman, Human::lessHumanHeight);
	std::cout << "Max height: " << maxHuman;
}
