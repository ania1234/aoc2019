#pragma once
#include <string>
#include <vector>

struct Vector2 {
public:
	int h;
	int w;
	Vector2(int h, int w);
};
class Problem10_1
{
public:
	Problem10_1();
	~Problem10_1();

	void Solve(std::string fileName);
	int FindConnections(int i, int j, std::vector<std::string> input);
	int Sign(int a);
	int LargestPrime(int n);
	int LargestCommonDenominator(int i, int j);
	void DeleteEverythingInLineOfSight(int i, int j, int h, int w, int height, int width, std::vector<Vector2> &neighbours, std::vector<std::string> &input);
};

