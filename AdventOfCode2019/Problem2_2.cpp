#include "pch.h"
#include "Problem2_2.h"
#include "Problem2_1.h"
#include "Problem1_1.h"
#include <iostream>


Problem2_2::Problem2_2()
{
}


Problem2_2::~Problem2_2()
{
}

void Problem2_2::Solve(std::string fileName)
{
	int winningOne;
	int winningTwo;
	int desiredOutput = 19690720;
	auto data = Problem1_1::ReadCommaDelimetedData(fileName);
	Problem2_1 computer;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int solution = computer.RunProgram(i, j, data);
			if (solution == desiredOutput) {
				winningOne = i;
				winningTwo = j;
			}
		}
	}

	std::cout << "WINNING ONE " << winningOne << std::endl;
	std::cout << "WINNING TWO " << winningTwo << std::endl;
}
