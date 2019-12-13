#include "pch.h"
#include <iostream>
#include "Problem1_2.h"
#include "Problem1_1.h"

Problem1_2::Problem1_2()
{
}


Problem1_2::~Problem1_2()
{
}

void Problem1_2::Solve(std::string fileName)
{
	long result = 0;
	auto data = Problem1_1::ReadNewLineDelimetedData(fileName);
	for (int input : data)
	{
		//std::cout << CalculateMass(input) << std::endl;
		result += CalculateMass(input);
	}
	std::cout << result << std::endl;
}

int Problem1_2::CalculateMass(int input)
{
	int result = -input;
	while (input > 0) {
		result += input;
		input = input / 3 - 2;
	}
	return result;
}
