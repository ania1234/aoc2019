#include "pch.h"
#include "Problem9_1.h"
#include "Problem1_1.h"
#include <iostream>

Problem9_1::Problem9_1()
{
}


Problem9_1::~Problem9_1()
{
}

void Problem9_1::Solve(std::string fileName)
{
	auto program = Problem1_1::ReadCommaDelimetedDataLong(fileName);
	Computer computer;
	int i = 0;
	computer.input.emplace_back(2);
	computer.program.clear();
	for (auto val : program) {
		computer.program[i] = val;
		i++;
	}
	computer.maxPlaceInMemory = program.size();
	computer.RunProgram();
	std::cout << computer.program[0] << std::endl;
}

std::vector<int64_t> Computer::RunProgram()
{
	std::vector<int64_t> output;
	int64_t relativeBase = 0;
	int64_t currentInstruction = 0;
	int currentInput = 0;
	int command = program[currentInstruction] % 100;
	int64_t arg1 = 0;
	int64_t arg2 = 0;
	int64_t dest = 0;
	int arg1Immediate = 0;
	int arg2Immediate = 0;
	int destImmediate = 0;
	bool usedInput = false;
	int ii = 0;
	while (command != 99) {
		command = program[currentInstruction] % 100;
		arg1Immediate = (program[currentInstruction] / 100) % 10;
		arg2Immediate = (program[currentInstruction] / 1000) % 10;
		//for now Dest is never immediate
		destImmediate = (program[currentInstruction] / 10000) % 10;
		switch (command) {
		case 1:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate == 0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (arg2Immediate == 0) {
				arg2 = program[arg2];
			}
			else if (arg2Immediate == 2) {
				arg2 = program[relativeBase + arg2];
			}
			dest = program[currentInstruction + 3];
			if (destImmediate == 2) {
				dest += relativeBase;
			}
			program[dest] = arg1 + arg2;
			currentInstruction += 4;
			break;
		case 2:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate == 0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (arg2Immediate == 0) {
				arg2 = program[arg2];
			}
			else if (arg2Immediate == 2) {
				arg2 = program[relativeBase + arg2];
			}
			dest = program[currentInstruction + 3];
			if (destImmediate == 2) {
				dest += relativeBase;
			}
			program[dest] = arg1 * arg2;
			currentInstruction += 4;
			break;
		case 3:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate == 2) {
				arg1 += relativeBase;
			}
			program[arg1] = input[currentInput];
			currentInput++;
			currentInstruction += 2;
			break;
		case 4:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate == 0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			std::cout <<"Partial result: "<< arg1 << std::endl;
			output.emplace_back( arg1);
			currentInstruction += 2;
			break;
		case 5:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate == 0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (arg2Immediate == 0) {
				arg2 = program[arg2];
			}
			else if (arg2Immediate == 2) {
				arg2 = program[relativeBase + arg2];
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
			if (arg1Immediate==0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (arg2Immediate==0) {
				arg2 = program[arg2];
			}
			else if (arg2Immediate == 2) {
				arg2 = program[relativeBase + arg2];
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
			if (arg1Immediate==0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (arg2Immediate==0) {
				arg2 = program[arg2];
			}
			else if (arg2Immediate == 2) {
				arg2 = program[relativeBase + arg2];
			}
			dest = program[currentInstruction + 3];
			if (destImmediate == 2) {
				dest += relativeBase;
			}
			program[dest] = arg1 < arg2;
			currentInstruction += 4;
			break;
		case 8:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate==0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			arg2 = program[currentInstruction + 2];
			if (arg2Immediate==0) {
				arg2 = program[arg2];
			}
			else if (arg2Immediate == 2) {
				arg2 = program[relativeBase + arg2];
			}
			dest = program[currentInstruction + 3];
			if (destImmediate == 2) {
				dest += relativeBase;
			}
			program[dest] = arg1 == arg2;
			currentInstruction += 4;
			break;
		case 9:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate == 0) {
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				arg1 = program[relativeBase + arg1];
			}
			relativeBase += arg1;
			currentInstruction += 2;
			break;
		case 99:
			return output;
			break;
		default:
			std::cout << "Weird command " << command << std::endl;
			break;
		}
	}
	return output;
}
