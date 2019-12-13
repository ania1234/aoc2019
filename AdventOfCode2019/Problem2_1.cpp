#include "pch.h"
#include "Problem2_1.h"
#include "Problem1_1.h"
#include <iostream>


Problem2_1::Problem2_1()
{
}


Problem2_1::~Problem2_1()
{
}

void Problem2_1::Solve(std::string fileName)
{
	auto data = Problem1_1::ReadCommaDelimetedData(fileName);
	RunProgram(12, 2, data);
}

int Problem2_1::RunProgram(int replace1, int replace2, std::vector<int> data)
{
	data[1] = replace1;
	data[2] = replace2;
	int currentInstruction = 0;
	int command = data[currentInstruction];
	int arg1 = data[currentInstruction + 1];
	int arg2 = data[currentInstruction + 2];
	int dest = data[currentInstruction + 3];
	while (command != 99) {
		arg1 = data[currentInstruction + 1];
		arg2 = data[currentInstruction + 2];
		dest = data[currentInstruction + 3];
		switch (command) {
		case 1:
			data[dest] = data[arg1] + data[arg2];
			break;
		case 2:
			data[dest] = data[arg1] * data[arg2];
			break;
		default:
			std::cout << "Weird command" << std::endl;
		}
		currentInstruction += 4;
		command = data[currentInstruction];
	}
	std::cout << "Result: " << data[0] << std::endl;
	return data[0];
}
