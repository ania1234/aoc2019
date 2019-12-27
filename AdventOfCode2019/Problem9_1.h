#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Computer {
public:
	std::unordered_map<int64_t, int64_t> program;
	int maxPlaceInMemory;
	std::vector<int64_t> input;
	std::vector<int64_t> RunProgram();
};
class Problem9_1
{
public:
	Problem9_1();
	~Problem9_1();
	void Solve(std::string fileName);
};

