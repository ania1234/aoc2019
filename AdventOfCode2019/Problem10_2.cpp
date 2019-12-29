#include "pch.h"
#include "Problem10_2.h"
#include <iostream>
#include <algorithm>
#include "Problem1_1.h"


Problem10_2::Problem10_2()
{

}


Problem10_2::~Problem10_2()
{
}

void Problem10_2::Solve(std::string fileName)
{
	auto input = Problem1_1::ReadAllLines(fileName);
	int heigth = input.size();
	int width = input[0].size();
	int maxConnections = 0;
	for (int h = 0; h < heigth; h++) {
		for (int w = 0; w < width; w++) {
			if (input[h][w] == '#') {
				int myConnections = Problem10_1::FindConnections(h, w, input).size();
				if (myConnections > maxConnections) {
					maxConnections = myConnections;
					maxH = h;
					maxW = w;
				}
			}
		}
	}
	std::cout << "Max connections " << maxConnections << std::endl;
	std::cout << "Max H " << maxH << std::endl;
	std::cout << "Max W " << maxW << std::endl;

	auto myNeighbours = Problem10_1::FindConnections(maxH, maxW, input);
	std::vector<Vector2> quarter1;
	std::vector<Vector2> quarter2;
	std::vector<Vector2> quarter3;
	std::vector<Vector2> quarter4;
	for (int i = 0; i < myNeighbours.size(); i++) {
		myNeighbours[i].y -= maxH;
		myNeighbours[i].x -= maxW;
	}

	for (auto n : myNeighbours) {
		if (n.y <= 0 && n.x >= 0) {
			quarter1.push_back(n);
		}
		if (n.y > 0 && n.x >= 0) {
			quarter2.push_back(n);
		}
		if (n.y > 0 && n.x < 0) {
			quarter3.push_back(n);
		}
		if (n.y <= 0 && n.x < 0) {
			quarter4.push_back(n);
		}
	}

	std::sort(quarter1.begin(), quarter1.end(), SortFunction);
	std::sort(quarter2.begin(), quarter2.end(), SortFunction);
	std::sort(quarter3.begin(), quarter3.end(), InvSortFunction);
	std::sort(quarter4.begin(), quarter4.end(), InvSortFunction);

	myNeighbours = quarter1;
	myNeighbours.insert(myNeighbours.end(), quarter2.begin(), quarter2.end());
	myNeighbours.insert(myNeighbours.end(), quarter3.begin(), quarter3.end());
	myNeighbours.insert(myNeighbours.end(), quarter4.begin(), quarter4.end());


	for (int i = 0; i < myNeighbours.size(); i++) {
		myNeighbours[i].y += maxH;
		myNeighbours[i].x += maxW;
	}

	for (int i = 0; i < myNeighbours.size(); i++) {
		std::printf("The %i th asteroid to be deleted is at position ( %i, %i ) wit sine = %f\n", i+1, myNeighbours[i].x, myNeighbours[i].y, ComputeSine(myNeighbours[i]) );
	}

	std::cout << "SOLUTION: " << myNeighbours[199].x * 100 + myNeighbours[199].y << std::endl;
}

//return true if i>j in our metric, false otherwise
bool Problem10_2::InvSortFunction(const Vector2 &i, const Vector2 &j)
{

	return ComputeSine(i) > ComputeSine(j);
}

//return true if i<j in our metric, false otherwise
bool Problem10_2::SortFunction(const Vector2 &i, const Vector2 &j)
{

	return ComputeSine(i) < ComputeSine(j);
}

float Problem10_2::ComputeSine(const Vector2 &i)
{
	int onX = i.y ;
	int onY = i.x ;
	return onX / (sqrt(onX*onX + onY * onY));
}

