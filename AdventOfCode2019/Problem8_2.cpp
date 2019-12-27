#include "pch.h"
#include "Problem8_2.h"
#include "Problem8_1.h"
#include <iostream>

Problem8_2::Problem8_2()
{
}


Problem8_2::~Problem8_2()
{
}

void Problem8_2::Solve(std::string fileName)
{
	auto input = Problem8_1::ReadLayers(fileName, 25, 6);
	std::vector<int> solution;
	for (int i = 0; i < 25 * 6; i++) {
		int layer = 0;
		while (input[layer][i] == 2) {
			layer++;
		}
		solution.emplace_back(input[layer][i]);
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 25; j++) {
			char c = solution[i * 25 + j] ? '#' : ' ';
			std::cout << c;
		}
		std::cout << std::endl;
	}
}
