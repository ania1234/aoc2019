#pragma once
#include <string>
#include <vector>
class Problem1_1
{
public:
	Problem1_1();
	~Problem1_1();
	void Solve(std::string fileName);
	static std::vector<int> ReadNewLineDelimetedData(std::string fileName);
	static std::vector<int> ReadCommaDelimetedData(std::string fileName);
	static std::vector<int64_t> ReadCommaDelimetedDataLong(std::string fileName);
	static std::vector<std::string> ReadAllLines(std::string fileName);
private:
	int CalculateMass(int input);
};

