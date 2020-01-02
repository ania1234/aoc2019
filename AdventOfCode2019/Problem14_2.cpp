#include "pch.h"
#include "Problem14_2.h"
#include "Problem1_1.h"
#include "Problem14_1.h"
#include <iostream>


Problem14_2::Problem14_2()
{
}


Problem14_2::~Problem14_2()
{
}

void Problem14_2::Solve(std::string fileName)
{
	auto allLines = Problem1_1::ReadAllLines(fileName);
	std::vector<Reaction> allReactions;
	for (auto line : allLines) {
		allReactions.emplace_back(Problem14_1::ReadReaction(line));
	}

	int myReactionIndex = 0;
	for (int i = 0; i < allReactions.size(); i++) {
		if (allReactions[i].rhs.name == "FUEL") {
			myReactionIndex = i;
		}
	}

	long long int maxOre = 1000000000000;


	//binary searchfor the right amount of fuel

	//first fuel that we can produce, that is too low in ore requirements for our liking
	long long int minFuel = maxOre/ Problem14_1::FindMinAmountForFuel(allReactions, 1);
	//first fuel that we can produce, that is too high in ore requirements for our liking
	long long int maxFuel = minFuel*2;

	long long int consideredFuel = (minFuel + maxFuel) / 2;

	while (consideredFuel != minFuel && consideredFuel != maxFuel) {
		long long int neededOreAmount = Problem14_1::FindMinAmountForFuel(allReactions, consideredFuel);
		std::cout << "Producing " << consideredFuel << " quantity of FUEL requires " << neededOreAmount << " ORE";
		if (neededOreAmount < maxOre) {
			std::printf(" TOO LOW!\n");
			minFuel = consideredFuel;
		}
		else {
			std::printf(" TOO HIGH!\n");
			maxFuel = consideredFuel;
		}
		consideredFuel = (minFuel + maxFuel) / 2;
	}

}
