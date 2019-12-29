#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Problem10_1.h"

class MockComputer {
public:
	std::unordered_map<long long int, long long int> program;
	std::vector<long long int> input;
	std::vector<long long int> RunProgram(int iterationNumber);
	int maxPlaceInMemory;
	bool finished = false;
private:
	long long int relativeBase = 0;
	long long int currentInstruction = 0;
	long long int currentInput = 0;
	long long int iteration = 0;
};


class ComputerWithBreaksEnabled {
public:
	std::unordered_map<int64_t, int64_t> program;
	std::vector<int64_t> input;
	std::vector<int64_t> RunProgram(int iterationNumber);
	int64_t maxPlaceInMemory;
	bool finished = false;
private:
	int64_t relativeBase = 0;
	int64_t currentInstruction = 0;
	int64_t currentInput = 0;
};

class Problem11_1
{
public:
	void Solve(std::string fileName);
	Vector2 ChooseDirection(Vector2 currentDirection, int right);
	Problem11_1();
	~Problem11_1();
	std::vector<Vector2> vectors;
	int GetVectorColor(Vector2 position);
	void ColorVector(Vector2 position, int color);
};

