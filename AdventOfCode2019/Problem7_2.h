#pragma once
#include <string>
#include <vector>
class Amplifier {
public:
	std::vector<int> program;
	int RunProgram(std::vector<int> input, std::vector<int> &data, bool shouldImmediatellyReturnOutput, int &returnCode);
};
class Problem7_2
{
public:
	Problem7_2();
	~Problem7_2();
	void Solve(std::string fileName);
};

