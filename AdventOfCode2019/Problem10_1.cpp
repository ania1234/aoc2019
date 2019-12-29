#include "pch.h"
#include "Problem10_1.h"
#include "Problem1_1.h"
#include <iostream>

Problem10_1::Problem10_1()
{
}


Problem10_1::~Problem10_1()
{
}

void Problem10_1::Solve(std::string fileName)
{
	//for (int i = 0; i < 30; i++) {
	//	std::cout << "Prime factors of " << i << " ";
	//	LargestPrime(i);
	//	std::cout << std::endl;
	//}
	auto input = Problem1_1::ReadAllLines(fileName);
	int heigth = input.size();
	int width = input[0].size();
	int maxConnections = 0;
	int maxI = -1;
	int maxJ = -1;
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			if (input[i][j] == '#') {
				int myConnections = FindConnections(i, j, input).size();
				if (myConnections > maxConnections) {
					maxConnections = myConnections;
					maxI = i;
					maxJ = j;
				}
			}
		}
	}
	std::cout << "Max connections " << maxConnections << std::endl;
	std::cout << "Max I " << maxI << std::endl;
	std::cout << "Max J " << maxJ << std::endl;
}

std::vector<Vector2> Problem10_1::FindConnections(int h, int w, std::vector<std::string> input)
{
	int heigth = input.size();
	int width = input[0].size();
	std::vector<Vector2> neighbours;
	input[h][w] = '.';

	//first Quarter
	for (int i = h; i < heigth; i++) {
		for (int j = w; j < width; j++) {
			if (input[i][j] != '.') {
				DeleteEverythingInLineOfSight(i, j, h, w, heigth, width, neighbours, input);
			}
		}
	}

	//secondQuarter
	for (int i = h; i < heigth; i++) {
		for (int j = w; j >=0; j--) {
			if (input[i][j] != '.') {
				DeleteEverythingInLineOfSight(i, j, h, w, heigth, width, neighbours, input);
			}
		}
	}

	//third quarter
	for (int i = h; i >= 0; i--) {
		for (int j = w; j >= 0; j--) {
			if (input[i][j] != '.') {
				DeleteEverythingInLineOfSight(i, j, h, w, heigth, width, neighbours, input);
			}
		}
	}

	//fourth quarter
	for (int i = h; i >= 0; i--) {
		for (int j = w; j < width; j++) {
			if (input[i][j] != '.') {
				DeleteEverythingInLineOfSight(i, j, h, w, heigth, width, neighbours, input);
			}
		}
	}


	std::string outputString;
	std::printf( "The asteroid at ( %i, %i ) has %i neighbours \n", w, h, neighbours.size());

	return neighbours;
}

int Problem10_1::LargestPrime(int n)
{
	//std::cout << "Prime factors of " << n << " ";
	int largestPrime = n>0?1:0;
	// Print the number of 2s that divide n  
	while (n % 2 == 0 && n>=2)
	{
		//std::cout << 2 << " ";
		largestPrime = 2;
		n = n / 2;
	}

	// n must be odd at this point. So we can skip  
	// one element (Note i = i +2)  
	for (int i = 3; i <= sqrt(n); i = i + 2)
	{
		// While i divides n, print i and divide n  
		while (n % i == 0 && n>0)
		{
			//std::cout << i << " ";
			largestPrime = i;
			n = n / i;
		}
	}

	// This condition is to handle the case when n  
	// is a prime number greater than 2  
	if (n > 2) {
		largestPrime = n;
		//std::cout << n << " ";
	}
	//std::cout << " Largest: " << largestPrime;
	//std::cout << std::endl;

	return largestPrime;
}

int Problem10_1::LargestCommonDenominator(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;
	else if (a == b)
		return a;
	else if (a > b)
		return LargestCommonDenominator(a - b, b);
	else return LargestCommonDenominator(a, b - a);
}

void Problem10_1::DeleteEverythingInLineOfSight(int i, int j, int h, int w, int height, int width, std::vector<Vector2>& neighbours, std::vector<std::string>& input)
{
	bool found = false;
	for (auto n : neighbours) {
		if (n.y == i && n.x == j) {
			found = true;
		}
	}
	if (!found) {
		neighbours.push_back(Vector2(i, j));
	}

	int largestCommonDenominator = LargestCommonDenominator(abs(i - h), abs(j - w));
	int moveHeight = (i - h) ;
	int moveWidth = (j - w) ;
	if (largestCommonDenominator != 0) {
		 moveHeight/=largestCommonDenominator;
		 moveWidth/=largestCommonDenominator;
	}
	if (moveHeight == moveWidth) {
		moveHeight = Sign(i - h);
		moveWidth = Sign(j - w);
	}
	if (moveWidth == 0) {
		moveHeight = Sign(i - h);
	}
	if (moveHeight == 0) {
		moveWidth = Sign(j - w);
	}
	int currDeleteH = i + moveHeight;
	int currDeleteW = j + moveWidth;

	while (currDeleteH >= 0 && currDeleteW >= 0 && currDeleteH<height && currDeleteW<width) {
		input[currDeleteH][currDeleteW] = '.';
		currDeleteH += moveHeight;
		currDeleteW += moveWidth;
	}
}


int Problem10_1::Sign(int a)
{
	return (a > 0) ? 1 : -1;
}

Vector2::Vector2(int h, int w)
{
	this->y = h;
	this->x = w;
}
