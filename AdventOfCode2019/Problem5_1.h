#pragma once
#include<string>
#include<vector>
class Problem5_1
{
public:
	Problem5_1();
	~Problem5_1();
	void Solve(std::string fileName);
	static int RunProgram(std::vector<int> input, std::vector<int> data, bool shouldImmediatellyReturnOutput, int &returnCode);
};

