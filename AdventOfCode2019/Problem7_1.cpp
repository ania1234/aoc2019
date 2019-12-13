#include "pch.h"
#include "Problem7_1.h"
#include "Problem1_1.h"
#include "Problem5_1.h"
#include <iostream>

Problem7_1::Problem7_1()
{
}


Problem7_1::~Problem7_1()
{
}

void Problem7_1::Solve(std::string fileName)
{
	auto program = Problem1_1::ReadCommaDelimetedData(fileName);

	int result = 0;
	int maxResult = 0;
	int returnCode = 0;
	std::vector<int> maxSequence;
	std::vector<int> input;
	std::vector<int> startInputSet{ 0, 1, 2, 3, 4 };
	std::vector<std::vector<int>> possiblePermutations;
	Permute(startInputSet, 0, 4, possiblePermutations);
	for (auto permutation : possiblePermutations) {
		result = 0;
		for (int i = 0; i < 5; i++) {
			input.clear();
			input.push_back(permutation[i]);
			input.push_back(result);
			result = Problem5_1::RunProgram(input, program, false, returnCode);
		}
		if (result > maxResult) {
			maxResult = result;
			maxSequence = permutation;
		}
	}
	std::cout << maxResult << std::endl;
}

void Problem7_1::Permute(std::vector<int> set, int leftIndex, int rightIndex, std::vector<std::vector<int>>& result)
{
	if (leftIndex == rightIndex)
		result.push_back(set);
	else
	{
		// Permutations made  
		for (int i = leftIndex; i <= rightIndex; i++)
		{

			// Swapping done  
			std::swap(set[leftIndex], set[i]);

			// Recursion called  
			Permute(set, leftIndex + 1, rightIndex, result);

			//backtrack  
			std::swap(set[leftIndex], set[i]);
		}
	}
}
