#pragma once
#include<string>
#include<vector>
#include "Problem10_1.h"
class Problem13_1
{
public:
	Problem13_1();
	~Problem13_1();
	void Solve(std::string fileName);
	static std::vector<Vector2> ReadGame(std::vector<int64_t> board, int& score, int& maxX, int& maxY);
	static std::vector<Vector2> ReadSomeGame(std::vector<int64_t> board, int& score);
	static void PrintGame(std::vector<Vector2> board, int score, int maxX, int maxY);
	static char ChooseChar(Vector2 tile);
	static void ClearConsole();
};

