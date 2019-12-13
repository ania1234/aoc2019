#include "pch.h"
#include "Problem3_2.h"
#include <iostream>

Problem3_2::Problem3_2()
{
}


Problem3_2::~Problem3_2()
{
}

int Problem3_2::GetLength(Point point, Line v, Line h)
{
	return v.stepsToStart + h.stepsToStart + abs(v.start.y - point.y) + abs(h.start.x - point.x);
}
