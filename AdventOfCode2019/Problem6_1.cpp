#include "pch.h"
#include "Problem6_1.h"
#include <iostream>
#include <fstream>

Problem6_1::Problem6_1()
{
}


Problem6_1::~Problem6_1()
{
}

void Problem6_1::Solve(std::string fileName)
{
	auto result = ReadPlanets(fileName);
	int r = result->CountOrbits(0);

	std::cout << r << std::endl;
}

Planet* Problem6_1::ReadPlanets(std::string fileName)
{
	Planet* parent = nullptr;
	std::ifstream inFile;
	std::string planetNameLeft;
	std::string planetNameRight;
	bool isRight = true;
	inFile.open(fileName);
	if (!inFile) {
		std::cout << "INVALID INPUT" << std::endl;
		return parent;
	}

	while (inFile.good()) {
		std::getline(inFile, planetNameLeft, ')');
		std::getline(inFile, planetNameRight, '\n');

		Planet* parentPlanet = allPlanets[planetNameLeft];
		if (parentPlanet == nullptr) {
			//std::cout << "EMPLACING POTENTIAL PARENT " << planetNameLeft << std::endl;
			allPlanets[planetNameLeft] = new Planet();
			parentPlanet = allPlanets[planetNameLeft];
			parentPlanet->name = planetNameLeft;
			parentPlanet->parent = nullptr;
			if (planetNameLeft == "COM") {
				std::cout << "HERE" << std::endl;
			}
		}


		//std::cout << "EMPLACING PLANET " << planetNameRight << std::endl;
		Planet* newPlanet = allPlanets[planetNameRight];
		if (newPlanet == nullptr) {
			allPlanets[planetNameRight] = new Planet();
			newPlanet = allPlanets[planetNameRight];
			newPlanet->name = planetNameRight;
		}
		newPlanet->parent = parentPlanet;
		parentPlanet->orbitters.emplace_back(newPlanet);
		allPlanets.emplace(newPlanet->name, newPlanet);
	}

	parent = allPlanets["COM"];
	return parent;
}



int Planet::CountOrbits(int depth)
{
	int result = depth;
	for (auto o : orbitters) {
		result += o->CountOrbits(depth + 1);
	}
	return result;
}
