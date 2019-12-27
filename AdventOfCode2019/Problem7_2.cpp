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
	std::vector<int> startInputSet{9, 8, 7, 6, 5 };
	std::vector<std::vector<int>> possiblePermutations;
	Problem7_1::Permute(startInputSet, 0, 4, possiblePermutations);
	int returnCode = 0;
	for(auto permutation : possiblePermutations)
	{
		std::cout << "Checking pair "<<permutation[0]<< permutation[1] << permutation[2]<< permutation[3]<< permutation[4]<< std::endl;
		result = 0;
		returnCode = 0;
		int i = 0;
		for (int a = 0; a < 5; a++) {
			amplifiers[a].program = program;
			amplifiers[a].phaseSetting = permutation[a];
			amplifiers[a].firstRun = true;
			amplifiers[a].currentInstruction = 0;
			amplifiers[a].finished = false;
			amplifiers[a].index = a;
		}
		while (!amplifiers[4].finished) {
			result = amplifiers[i].RunProgram( result);
			//std::cout << "Amplifier " << i << " returns " << result<<std::endl;
			i++;
			i = i % 5;
		}
		std::cout << amplifiers[4].RunProgram(result) << std::endl;
		if (result > maxResult) {
			maxResult = result;
			maxSequence = permutation;
		}
	}
	std::cout << maxResult << std::endl;
}

int Amplifier::RunProgram(int input)
{
	int command = program[currentInstruction] % 100;
	int arg1 = 0;
	int arg2 = 0;
	int dest = 0;
	int arg1Immediate = 0;
	int arg2Immediate = 0;
	int destImmediate = 0;
	bool usedInput = false;
	int ii = 0;
	while (command != 99) {
		command = program[currentInstruction] % 100;
		arg1Immediate = (program[currentInstruction] / 100) % 2;
		arg2Immediate = (program[currentInstruction] / 1000) % 2;
		//for now Dest is never immediate
		destImmediate = (program[currentInstruction] / 10000) % 2;
		switch (command) {
		case 1:
			arg1 = program[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = program[arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = program[arg2];
			}
			dest = program[currentInstruction + 3];
			program[dest] = arg1 + arg2;
			currentInstruction += 4;
			break;
		case 2:
			arg1 = program[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = program[arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = program[arg2];
			}
			dest = program[currentInstruction + 3];
			program[dest] = arg1 * arg2;
			currentInstruction += 4;
			break;
		case 3:
			arg1 = program[currentInstruction + 1];
			if (firstRun) {
				ii = phaseSetting;
				firstRun = false;
			}
			else if (usedInput) {
				std::cout << "Trying to get input even though input was used";
				return output;
			}
			else {
				ii = input;
				usedInput = true;
			}
			program[arg1] = ii;
			//std::cout << program[currentInstruction] << std::endl;
			//std::cout << "Amplifier " << index << " calls for input, gets " << ii << std::endl;
			currentInstruction += 2;
			break;
		case 4:
			arg1 = program[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = program[arg1];
			}
			//std::cout <<"Partial result: "<< arg1 << std::endl;
			output = arg1;
			currentInstruction += 2;
			if (program[currentInstruction] != 99) {

				return output;
			}
			break;
		case 5:
			arg1 = program[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = program[arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = program[arg2];
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
			arg1 = program[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = program[arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = program[arg2];
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
			arg1 = program[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = program[arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = program[arg2];
			}
			dest = program[currentInstruction + 3];
			program[dest] = arg1 < arg2;
			currentInstruction += 4;
			break;
		case 8:
			arg1 = program[currentInstruction + 1];
			if (!arg1Immediate) {
				arg1 = program[arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (!arg2Immediate) {
				arg2 = program[arg2];
			}
			dest = program[currentInstruction + 3];
			program[dest] = arg1 == arg2;
			currentInstruction += 4;
			break;
		case 99:
			finished = true;
			return output;
			break;
		default:
			std::cout << "Weird command " << command << std::endl;
			break;
		}
	}
	return output;
}
