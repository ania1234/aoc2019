#pragma once
#include <string>
#include <vector>

struct Vector2 {
public:
	int y;
	int x;
	int color;
	Vector2(int y, int x);
};
class Problem10_1
{
public:
	Problem10_1();
	~Problem10_1();

	void Solve(std::string fileName);
	static std::vector<Vector2> FindConnections(int i, int j, std::vector<std::string> input);
	static int Sign(int a);
	int LargestPrime(int n);
	static int LargestCommonDenominator(int i, int j);
	static void DeleteEverythingInLineOfSight(int i, int j, int h, int w, int height, int width, std::vector<Vector2> &neighbours, std::vector<std::string> &input);
};

