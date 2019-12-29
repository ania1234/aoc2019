#pragma once
#include "Problem10_1.h"

class Problem10_2
{
public:
	Problem10_2();
	~Problem10_2();
	void Solve(std::string fileName);
	static bool SortFunction(const Vector2 &i, const Vector2 &j);
	static bool InvSortFunction(const Vector2 &i, const Vector2 &j);
	static float ComputeSine(const Vector2 &i);
private:
	 int maxH;
	 int maxW;
};

