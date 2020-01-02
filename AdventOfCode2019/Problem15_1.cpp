#include "pch.h"
#include "Problem15_1.h"
#include "Problem1_1.h"
#include "Problem11_1.h"
#include <SFML/Graphics.hpp>


Problem15_1::Problem15_1()
{
}


Problem15_1::~Problem15_1()
{
}

void Problem15_1::Solve(std::string fileName)
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
}
