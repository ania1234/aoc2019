#include "pch.h"
#include <iostream>
#include "Problem6_2.h"
#include "Problem6_1.h"

Problem6_2::Problem6_2()
{
}


Problem6_2::~Problem6_2()
{
}

void Problem6_2::Solve(std::string fileName)
{
	Problem6_1 reader;
	reader.ReadPlanets(fileName);
	auto youRoute = GetRouteToCOM(reader.allPlanets["YOU"]);
	auto sanRoute = GetRouteToCOM(reader.allPlanets["SAN"]);
	int numberCommon = 0;
	while (numberCommon < sanRoute.size() && numberCommon < youRoute.size() &&
		sanRoute[sanRoute.size()-1-numberCommon] == youRoute[youRoute.size()-1-numberCommon]) {
		numberCommon++;
	}
	int result = sanRoute.size() - numberCommon + youRoute.size() - numberCommon;
	std::cout << result << std::endl;
}

std::vector<Planet*> Problem6_2::GetRouteToCOM(Planet* start)
{
	std::vector<Planet*> result;
	Planet* parent = start->parent;
	while (parent != nullptr) {
		result.emplace_back(parent);
		parent = parent->parent;
	}
	return result;
}
