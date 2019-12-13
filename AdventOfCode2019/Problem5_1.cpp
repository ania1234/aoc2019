#include "pch.h"
#include "Problem5_1.h"
#include "Problem1_1.h"
#include <iostream>

Problem5_1::Problem5_1()
{
}


Problem5_1::~Problem5_1()
{
}

void Problem5_1::Solve(std::string fileName)
{
	auto data = Problem1_1::ReadCommaDelimetedData(fileName);
	std::vector<int> input;
	input.emplace_back(5);
	int returnCode = 0;
	auto result = RunProgram(input, data, false, returnCode);
	std::cout << result << std::endl;
}

int Problem5_1::RunProgram(std::vector<int> input, std::vector<int> data, bool shouldImmediatellyReturnOutput, int& returnCode)
{
	int currentInstruction = 0;
	int command = data[currentInstruction]%100;
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
		command = data[currentInstruction]%100;
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
			//std::cout <<"Partial result: "<< arg1 << std::endl;
			output = arg1;
			if (shouldImmediatellyReturnOutput && data[currentInstruction+2]!=99) {
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
