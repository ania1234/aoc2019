#pragma once
#include <string>
#include <vector>
class Planet;
class Problem6_2
{
public:
	Problem6_2();
	~Problem6_2();
	void Solve(std::string fileName);
	std::vector<Planet*> GetRouteToCOM(Planet* start);
};

