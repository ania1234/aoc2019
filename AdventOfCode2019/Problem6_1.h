#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Planet {
public:
	std::vector<Planet*> orbitters;
	std::string name;
	Planet* parent;
	int CountOrbits(int depth);
};

class Problem6_1
{
public:
	Problem6_1();
	~Problem6_1();
	void Solve(std::string fileName);
	Planet* ReadPlanets(std::string fileName);
	std::unordered_map<std::string, Planet*> allPlanets;
};

