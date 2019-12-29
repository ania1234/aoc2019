#include "pch.h"
#include "Problem11_1.h"
#include "Problem10_1.h"
#include "Problem1_1.h"
#include <iostream>

void Problem11_1::Solve(std::string fileName)
{
	Vector2 currentDirection(0,-1);
	Vector2 currentPosition(0, 0);
	auto program = Problem1_1::ReadCommaDelimetedDataLong(fileName);
	ComputerWithBreaksEnabled computer;
	int i = 0;
	computer.input.emplace_back(1);
	computer.program.clear();
	for (auto val : program) {
		computer.program[i] = val;
		i++;
	}
	computer.maxPlaceInMemory = program.size();
	std::string s;
	std::vector<int64_t> output;
	i = 0;
	do  
	{
		output = computer.RunProgram(i);

		if (!computer.finished)
		{
			std::cout << "(" << i << ") " << output[0] << " " << output[1] << " pos: [" << currentPosition.x << ", " << currentPosition.y << "]" << std::endl;
			//std::cin >> s;
			i++;
			ColorVector(currentPosition, output[0]);
			Vector2 newPosition = currentPosition;
			Vector2 newDirection = ChooseDirection(currentDirection, output[1]);
			newPosition.y += newDirection.y;
			newPosition.x += newDirection.x;
			currentPosition = newPosition;
			currentDirection = newDirection;
			computer.input.emplace_back(GetVectorColor(currentPosition));
		}
	} while (!computer.finished);
	std::cout << vectors.size() << std::endl;

	for (int y = 0; y < 6; y++) 
	{
		for (int x = 0; x < 41; x++) 
		{
			int myInt = GetVectorColor(Vector2(x, y));
			char myChar = myInt > 0 ? '#' : ' ';
			std::cout << myChar;
		}
		std::cout<< std::endl;
	}

	std::cout << computer.program[0] << std::endl;
}

Vector2 Problem11_1::ChooseDirection(Vector2 currentDirection, int right)
{
	Vector2 result(0, 0);
	switch (right) {
	case 0:
		result.x = -currentDirection.y;
		result.y = currentDirection.x;
		return result;
	case 1:
		result.x = currentDirection.y;
		result.y = -currentDirection.x;
		return result;
	};

	std::cout << "ERROR" << std::endl;
	return Vector2(0, 0);
}

Problem11_1::Problem11_1()
{
}


Problem11_1::~Problem11_1()
{
}

std::vector<int64_t> ComputerWithBreaksEnabled::RunProgram(int iterationNumber)
{
	std::vector<int64_t> output;
	int command = program[currentInstruction] % 100;
	int64_t arg1 = 0;
	int64_t arg2 = 0;
	int64_t dest = 0;
	int arg1Immediate = 0;
	int arg2Immediate = 0;
	int destImmediate = 0;
	while (command != 99) {
		//std::cout << currentInstruction << std::endl;
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
			if (input.size() <= currentInput) {
				//std::cout << "returning  output " << output[0]<< std::endl;
				return output;
			}
			//std::cout << "Getting input " << input[currentInput] << std::endl;
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
			//std::cout << "Partial result: " << arg1 << std::endl;
			output.emplace_back(arg1);
			currentInstruction += 2;
			break;
		case 5:
			arg1 = program[currentInstruction + 1];
			if (arg1Immediate == 0) {
				//std::cout << "arg1Immediate == 0" << std::endl;
				arg1 = program[arg1];
			}
			else if (arg1Immediate == 2) {
				std::cout << "arg1Immediate == 2" << std::endl;
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
				//std::cout << "Jump" << std::endl;
				currentInstruction = arg2;
			}
			else {
				std::cout << "WTF" << std::endl;
				currentInstruction += 3;
			}
			break;
		case 6:
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
			program[dest] = arg1 < arg2;
			currentInstruction += 4;
			break;
		case 8:
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
	finished = true;
	return output;
}

int Problem11_1::GetVectorColor(Vector2 position)
{
	int result = 0;
	bool found = false;
	for (auto v : vectors) {
		if (v.y == position.y && v.x == position.x) {
			result =  v.color;
			found = true;
		}
	}

	if (!found) {
		//std::cout << "Not found" << std::endl;
	}
	//std::printf("Getting vector color for ( %i, %i ): %i\n", position.x, position.y, result);
	return result;
}

void Problem11_1::ColorVector(Vector2 position, int color)
{
	//std::printf("Setting vector color for ( %i, %i ): %i ", position.x, position.y, color);
	for (int i = 0; i < vectors.size(); i++) {
		if (vectors[i].y == position.y && vectors[i].x == position.x) {
			//std::printf(" Set on found\n");
			vectors[i].color = color;
			return;
		}
	}

	Vector2 added(position.y, position.x);
	added.color = color;
	//std::printf(" Set on NOT found\n");
	vectors.emplace_back(added);
}

std::vector<int64_t> MockComputer::RunProgram(int iterationNumber)
{
	std::vector<int64_t> result;

	switch (iteration) {
	case 0:
		result.emplace_back(1);
		result.emplace_back(0);
		break;
	case 1:
		result.emplace_back(0);
		result.emplace_back(0);
		break;
	case 2:
		result.emplace_back(1);
		result.emplace_back(0);
		break;
	case 3:
		std::cout << input[3] << std::endl;
		result.emplace_back(1);
		result.emplace_back(0);
		break;
	case 4:
		result.emplace_back(0);
		result.emplace_back(1);
		break;
	case 5:
		result.emplace_back(1);
		result.emplace_back(0);
		break;
	case 6:
		result.emplace_back(1);
		result.emplace_back(0);
		break;
	case 7:
		finished = true;
		break;

	}
	iteration++;
	return result;
}
