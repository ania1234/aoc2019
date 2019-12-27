#include "pch.h"
#include "Problem8_1.h"
#include <iostream>
#include <fstream>

Problem8_1::Problem8_1()
{
}


Problem8_1::~Problem8_1()
{
}

void Problem8_1::Solve(std::string fileName)
{
	auto data = ReadLayers(fileName, 25, 6);
	int minNumZeros = 25*6;
	int result;
	for (auto layer : data) {
		int num0 =0 ;
		int num1 =0;
		int num2 =0;
		Count012(layer, num0, num1, num2);
		if (num0 < minNumZeros) {
			minNumZeros = num0;
			result = num1 * num2;
		}
	}
	std::cout << result << std::endl;
}

std::vector<std::vector<int>> Problem8_1::ReadLayers(std::string fileName, int width, int height)
{
	std::vector<std::vector<int>> result;
	std::ifstream inFile;
	std::string line;
	inFile.open(fileName);
	if (!inFile) {
		std::cout << "INVALID INPUT" << std::endl;
		return result;
	}
	do
	{
		std::vector<int> partial;
		for (int i = 0; i < width*height; i++) {
			partial.emplace_back(inFile.get()-48);
		}
		result.emplace_back(partial);
	} while (inFile.peek()>0);
	return result;
}

void Problem8_1::Count012(std::vector<int> input, int & num0, int & num1, int & num2)
{
	num0 = num1 = num2 = 0;
	for (int i : input) {
		switch (i) {
		case 0:
			num0++;
			break;
		case 1:
			num1++;
			break;
		case 2:
			num2++;
			break;
		default:
			std::cout << "WEIRD NUMBER " << i << std::endl;
			break;
		}
	}
}
