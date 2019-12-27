#include "pch.h"
#include "Problem1_1.h"
#include <iostream>
#include <fstream>

Problem1_1::Problem1_1()
{
}


Problem1_1::~Problem1_1()
{
}

void Problem1_1::Solve(std::string fileName)
{
	long result = 0;
	auto data = ReadNewLineDelimetedData(fileName);
	for (int input : data)
	{
		result+= CalculateMass(input);
	}
	std::cout << result << std::endl;
}

std::vector<int> Problem1_1::ReadNewLineDelimetedData(std::string fileName)
{
	std::ifstream inFile;
	std::vector<int> result;
	int x;
	inFile.open(fileName);
	if (!inFile) {
		std::cout << "INVALID INPUT" << std::endl;
		return result;
	}

	while (inFile >> x) {
		result.emplace_back(x);
	}

	inFile.close();
	return result;
}

std::vector<int64_t> Problem1_1::ReadCommaDelimetedDataLong(std::string fileName)
{
	std::vector<int64_t> result;
	std::ifstream inFile;
	int64_t x;
	std::string line;
	inFile.open(fileName);
	if (!inFile) {
		std::cout << "INVALID INPUT" << std::endl;
		return result;
	}
	while (inFile.good()) {
		std::getline(inFile, line, ',');
		x = std::stoll(line);
		result.emplace_back(x);
	}
	return result;
}

std::vector<std::string> Problem1_1::ReadAllLines(std::string fileName)
{
	std::vector<std::string> result;
	std::string line;
	std::ifstream inFile;
	inFile.open(fileName);
	if (!inFile) {
		std::cout << "INVALID INPUT" << std::endl;
		return result;
	}
	while (inFile.good()) {
		std::getline(inFile, line, '\n');
		result.emplace_back(line);
	}
	return result;
}

std::vector<int> Problem1_1::ReadCommaDelimetedData(std::string fileName)
{
	std::vector<int> result;
	std::ifstream inFile;
	int x;
	std::string line;
	inFile.open(fileName);
	if (!inFile) {
		std::cout << "INVALID INPUT" << std::endl;
		return result;
	}
	while (inFile.good()) {
		std::getline(inFile, line, ',');
		x = std::stoi(line);
		result.emplace_back(x);
	}
	return result;
}

int Problem1_1::CalculateMass(int input)
{
	return input / 3 - 2;
}
