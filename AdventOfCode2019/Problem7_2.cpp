#include "pch.h"
#include "Problem7_2.h"
#include "Problem7_1.h"
#include "Problem1_1.h"
#include "Problem5_1.h"
#include <iostream>

Problem7_2::Problem7_2()
{
}


Problem7_2::~Problem7_2()
{
}

void Problem7_2::Solve(std::string fileName)
{
	auto program = Problem1_1::ReadCommaDelimetedData(fileName);

	int result = 0;
	int maxResult = 0;
	Amplifier amplifiers[5];
	std::vector<int> maxSequence;
	std::vector<int> input;
	std::vector<int> startInputSet{9, 8, 7, 6, 5 };
	std::vector<std::vector<int>> possiblePermutations;
	Problem7_1::Permute(startInputSet, 0, 4, possiblePermutations);
	int returnCode = 0;
	for (auto permutation : possiblePermutations) {
		std::cout << "Checking pair "<<permutation[0]<< permutation[1] << permutation[2]<< permutation[3]<< permutation[4]<< std::endl;
		result = 0;
		returnCode = 0;
		int i = 0;
		for (int a = 0; a < 5; a++) {
			amplifiers[a].program = program;
		}
		while (returnCode == 0) {
			input.clear();
			input.push_back(permutation[i]);
			input.push_back(result);
			result = amplifiers[i].RunProgram(input, amplifiers[i].program, true, returnCode);

				std::cout << "Result at " << i << std::endl;
				std::cout << result << std::endl;

			i++;
			i = i % 5;
		}
		if (result > maxResult) {
			maxResult = result;
			maxSequence = permutation;
		}
	}
	std::cout << maxResult << std::endl;
}

int Amplifier::RunProgram(std::vector<int> input, std::vector<int> &data, bool shouldImmediatellyReturnOutput, int & returnCode)
{
	int currentInstruction = 0;
	int command = data[currentInstruction] % 100;
	int arg1 = 0;
	int arg2 = 0;
	int dest = 0;
	int arg1Immediate = 0;
	int arg2Immediate = 0;
	int destImmediate = 0;
	int currentInput = 0;
	int output = 0;
	returnCode = 0;
	while (command != 99) {
		command = data[currentInstruction] % 100;
		arg1Immediate = (data[currentInstruction] / 100) % 2;
		arg2Immediate = (data[currentInstruction] / 1000) % 2;
		//for now Dest is never immediate
		destImmediate = (data[currentInstruction] / 10000) % 2;
		switch (command) {
		case 1:
			arg1 = data[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = data[arg1];
			}
			arg2 = data[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = data[arg2];
			}
			dest = data[currentInstruction + 3];
			data[dest] = arg1 + arg2;
			currentInstruction += 4;
			break;
		case 2:
			arg1 = data[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = data[arg1];
			}
			arg2 = data[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = data[arg2];
			}
			dest = data[currentInstruction + 3];
			data[dest] = arg1 * arg2;
			currentInstruction += 4;
			break;
		case 3:
			arg1 = data[currentInstruction + 1];
			data[arg1] = input[currentInput];
			currentInstruction += 2;
			currentInput++;
			break;
		case 4:
			arg1 = data[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = data[arg1];
			}
			output = arg1;
			if (shouldImmediatellyReturnOutput && data[currentInstruction + 2] != 99) {
				return output;
			}
			currentInstruction += 2;
			break;
		case 5:
			arg1 = data[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = data[arg1];
			}
			arg2 = data[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = data[arg2];
			}
			if (arg1 != 0)
			{
				currentInstruction = arg2;
			}
			else {
				currentInstruction += 3;
			}
			break;
		case 6:
			arg1 = data[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = data[arg1];
			}
			arg2 = data[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = data[arg2];
			}
			if (arg1 == 0)
			{
				currentInstruction = arg2;
			}
			else {
				currentInstruction += 3;
			}
			break;
		case 7:
			arg1 = data[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = data[arg1];
			}
			arg2 = data[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = data[arg2];
			}
			dest = data[currentInstruction + 3];
			data[dest] = arg1 < arg2;
			currentInstruction += 4;
			break;
		case 8:
			arg1 = data[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = data[arg1];
			}
			arg2 = data[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = data[arg2];
			}
			dest = data[currentInstruction + 3];
			data[dest] = arg1 == arg2;
			currentInstruction += 4;
			break;
		case 99:
			std::cout << "Output at immediate exit command: " << output << std::endl;
			returnCode = 99;
			break;
		default:
			std::cout << "Weird command " << command << std::endl;
			break;
		}
	}
	return output;
}
