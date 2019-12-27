#pragma once
#include <vector>

class Problem8_1
{
public:
	Problem8_1();
	~Problem8_1();

	void Solve(std::string fileName);
	static std::vector<std::vector<int>> ReadLayers(std::string fileName, int width, int height);
private:
	void Count012(std::vector<int> input, int& num0, int& num1, int& num2);
};

