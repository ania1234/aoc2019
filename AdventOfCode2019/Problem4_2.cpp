#include "pch.h"
#include "Problem4_2.h"


Problem4_2::Problem4_2()
{
}


Problem4_2::~Problem4_2()
{
}

bool Problem4_2::IsNumberCorrect(int number)
{
	bool isTwoConsecutive = false;
	int consecutiveCounter = 0;
	int currentNum = number % 10;
	number /= 10;
	while (number > 0) {
		int nextNum = number % 10;
		if (nextNum > currentNum) {
			return false;
		}
		if (nextNum == currentNum) {
			consecutiveCounter++;
		}
		else {
			if (consecutiveCounter == 1) {
				isTwoConsecutive = true;
			}
			consecutiveCounter = 0;
		}
		currentNum = nextNum;
		number /= 10;
	}
	if (consecutiveCounter == 1) {
		isTwoConsecutive = true;
	}
	consecutiveCounter = 0;
	return isTwoConsecutive;
}
