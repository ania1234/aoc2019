#pragma once
#include "Problem3_1.h"

class Problem3_2 : public Problem3_1
{
public:
	Problem3_2();
	~Problem3_2();
	int GetLength(Point point, Line v, Line h) override;
};

