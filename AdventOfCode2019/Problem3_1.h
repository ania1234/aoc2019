#pragma once
#include <string>
#include <vector>

struct Point
{
	int x;
	int y;
};

struct Line
{
	Point start;
	Point end;
	int stepsToStart;
};

struct Wire 
{
	std::vector<Line> horizontalLines;
	std::vector<Line> verticalLines;
};

class Problem3_1
{
public:
	Problem3_1();
	~Problem3_1();
	void Solve(std::string fileName);
	virtual int GetLength(Point point, Line v, Line h) ;
private:
	std::pair<Wire, Wire> ReadWires(std::string fileName);
	std::vector<int> GetOverlappingPointsDistances(std::vector<Line> horizontalLines, std::vector<Line> verticalLines);
};

