#include "pch.h"
#include "Problem4_1.h"
#include <iostream>
#include <string>

Problem4_1::Problem4_1()
{
}


Problem4_1::~Problem4_1()
{
}

void Problem4_1::Solve(int minNumber, int maxNumber)
{
	std::cout << IsNumberCorrect(112223) << std::endl;
	std::cout << IsNumberCorrect(123444) << std::endl;
	std::cout << IsNumberCorrect(111122) << std::endl;
	int result = 0;
	for (int i = minNumber; i <= maxNumber; i++) {
		if (IsNumberCorrect(i)) {
			result++;
		}
	}
	std::cout << result << std::endl;
}

bool Problem4_1::IsNumberCorrect(int number)
{
	bool isTwoConsecutive = false;
	int currentNum = number % 10;
	number /= 10;
	while (number > 0) {
		int nextNum = number % 10;
		if (nextNum > currentNum) {
			return false;
		}
		if (nextNum == currentNum) {
			isTwoConsecutive = true;
		}
		currentNum = nextNum;
		number /= 10;
	}
	return isTwoConsecutive;
}
