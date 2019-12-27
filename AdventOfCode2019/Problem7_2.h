#pragma once
#include <string>
#include <vector>
class Amplifier {
public:
	std::vector<int> program;
	int currentInstruction = 0;
	bool firstRun = true;
	bool finished = false;
	int output;
	int phaseSetting;
	int RunProgram(int input);
	int index;
};
class Problem7_2
{
public:
	Problem7_2();
	~Problem7_2();
	void Solve(std::string fileName);
};

