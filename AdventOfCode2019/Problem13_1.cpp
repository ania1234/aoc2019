#include "pch.h"
#include "Problem13_1.h"
#include "Problem11_1.h"
#include "Problem1_1.h"
#include <iostream>


Problem13_1::Problem13_1()
{
}


Problem13_1::~Problem13_1()
{
}

void Problem13_1::Solve(std::string fileName)
{
	auto program = Problem1_1::ReadCommaDelimetedDataLong(fileName);
	ComputerWithBreaksEnabled computer;
	int i = 0;
	computer.program.clear();
	for (auto val : program) {
		computer.program[i] = val;
		i++;
	}
	computer.maxPlaceInMemory = program.size();
	auto output = computer.RunProgram(0);
	for (auto val : output) {
		std::cout << val << std::endl;
	}
}
