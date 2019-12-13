#pragma once
#include <string>
#include <vector>
class Problem7_1
{
public:
	Problem7_1();
	~Problem7_1();
	void Solve(std::string fileName);
	static void Permute(std::vector<int> set, int leftIndex, int rightIndex, std::vector<std::vector<int>> &result);
};

