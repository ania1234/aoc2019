#include "pch.h"
#include "Problem3_1.h"
#include <iostream>
#include <fstream>
#include <sstream>

Problem3_1::Problem3_1()
{
}


Problem3_1::~Problem3_1()
{
}

void Problem3_1::Solve(std::string fileName)
{
	auto input = ReadWires(fileName);
	int minDistance = INT32_MAX;
	auto pointsHW = GetOverlappingPointsDistances(input.first.horizontalLines, input.second.verticalLines);
	for (int p : pointsHW) {
		if (p < minDistance) {
			minDistance = p;
		}
	}
	auto pointsWH = GetOverlappingPointsDistances(input.second.horizontalLines, input.first.verticalLines);
	for (int p : pointsWH) {
		if (p < minDistance) {
			minDistance = p;
		}
	}
	std::cout << minDistance << std::endl;
}

std::pair<Wire, Wire> Problem3_1::ReadWires(std::string fileName)
{
	Wire resultArray[2];
	std::pair<Wire, Wire> result;
	std::ifstream inFile;
	std::string line;
	std::string singleElement;
	Point origin;
	Point newPoint;
	Line lineSegment;
	char movementDirection;
	int movementMagnitude;
	int wireIndex =0;
	int stepsToStart = 0;
	inFile.open(fileName);
	if (!inFile) {
		std::cout << "INVALID INPUT" << std::endl;
		return result;
	}
	while (inFile.good()) {
		std::getline(inFile, line, '\n');
		std::stringstream ss(line);
		origin.x = 0;
		origin.y = 0;
		stepsToStart = 0;
		while (ss.good()) {
			std::getline(ss, singleElement, ',');
			movementDirection = singleElement[0];
			movementMagnitude = std::stoi(singleElement.substr(1, singleElement.length() - 1));
			newPoint.x = origin.x;
			newPoint.y = origin.y;
			switch (movementDirection) {
			case 'L':
				newPoint.x -= movementMagnitude;
				break;
			case 'R':
				newPoint.x += movementMagnitude;
				break;
			case 'U':
				newPoint.y += movementMagnitude;
				break;
			case 'D':
				newPoint.y -= movementMagnitude;
				break;
			default:
				break;
			}
			lineSegment.stepsToStart = stepsToStart;
			lineSegment.start = origin;
			lineSegment.end = newPoint;
			origin = newPoint;
			stepsToStart += movementMagnitude;
			if (movementDirection == 'L' || movementDirection == 'R') {
				resultArray[wireIndex].horizontalLines.emplace_back(lineSegment);
			}
			else {
				resultArray[wireIndex].verticalLines.emplace_back(lineSegment);
			}
		}
		wireIndex++;
	}
	result.first = resultArray[0];
	result.second = resultArray[1];
	return result;
}

std::vector<int> Problem3_1::GetOverlappingPointsDistances(std::vector<Line> horizontalLines, std::vector<Line> verticalLines)
{
	std::vector<int> result;
	for (auto h : horizontalLines) {
		for (auto v : verticalLines) {
			bool hCrossesV = (h.start.x < v.start.x && h.end.x > v.start.x) || (h.start.x > v.start.x && h.end.x < v.start.x);
			bool vCrossesH = (v.start.y < h.start.y && v.end.y > h.start.y) || (v.start.y > h.start.y && v.end.y < h.start.y);
			if (vCrossesH && hCrossesV) {
				Point found;
				found.x = v.start.x;
				found.y = h.start.y;
				result.emplace_back(GetLength(found, v, h));
			}
		}
	}
	return result;
}

int Problem3_1::GetLength(Point point, Line v, Line h)
{
	return abs(point.x) + abs(point.y);
}
