#include "pch.h"
#include "Problem12_2.h"
#include <vector>
#include <iostream>
#include "Problem12_1.h"
#include "Problem10_1.h"


Problem12_2::Problem12_2()
{

}


Problem12_2::~Problem12_2()
{
}

void Problem12_2::Solve()
{
	std::vector<Moon> moons;
	std::vector<Moon> initial;

	//smaller input
	//moons.emplace_back(Moon(-1, 0, 2));
	//moons.emplace_back(Moon(2, -10, -7));
	//moons.emplace_back(Moon(4, -8, 8));
	//moons.emplace_back(Moon(3, 5, -1));

	////bigger input
	//moons.emplace_back(Moon(-8, -10, 0));
	//moons.emplace_back(Moon(5, 5, 10));
	//moons.emplace_back(Moon(2, -7, 3));
	//moons.emplace_back(Moon(9, -8, -3));

	////my input
	moons.emplace_back(Moon(-3, 15, -11));
	moons.emplace_back(Moon(3, 13, -19));
	moons.emplace_back(Moon(-13, 18, -2));
	moons.emplace_back(Moon(6, 0, -1));

	for (int i = 0; i < moons.size(); i++) {
		Moon m = moons[i];
		initial.emplace_back(m);
	}

	long long int stepX = 0;
	long long int stepY = 0;
	long long int stepZ = 0;
	long long int step = 0;
	bool found = false;
	int size = moons.size();
	while (!stepX || !stepY || !stepZ) {
		if (step % 1000000 == 0) {
			std::printf("Step: %i\n", step);
		}
		//for (int i = 0; i < moons.size(); i++) {
		//	moons[i].PrintPosition();
		//}
		//apply gravity
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				moons[i].UpdateVelocityAndOther(&moons[j]);
			}
		}
		//update position
		for (int i = 0; i < size; i++) {
			moons[i].UpdatePosition();
		}
		step++;

		found = true;
		for (int i = 0; i < size; i++) {
			if (initial[i].position.x != moons[i].position.x || initial[i].velocity.x != moons[i].velocity.x) {
				found = false;
			}
		}
		if (found && !stepX) {
			stepX = step;
		}

		found = true;
		for (int i = 0; i < size; i++) {
			if (initial[i].position.y != moons[i].position.y || initial[i].velocity.y != moons[i].velocity.y) {
				found = false;
			}
		}
		if (found && !stepY) {
			stepY = step;
		}

		found = true;
		for (int i = 0; i < size; i++) {
			if (initial[i].position.z != moons[i].position.z || initial[i].velocity.z != moons[i].velocity.z) {
				found = false;
			}
		}
		if (found && !stepZ) {
			stepZ = step;
		}
	}


	std::cout << "Step X: " << stepX << std::endl;
	std::cout << "Step Y: " << stepY << std::endl;
	std::cout << "Step Z: " << stepZ << std::endl;

	auto smpYZ = SmallestCommonMultiplication(stepY, stepZ);

	std::cout << "Solution: " << SmallestCommonMultiplication(stepX, smpYZ);
}

long long int Problem12_2::SmallestCommonMultiplication(long long int x, long long int y)
{
	long long int base = x > y ? x : y;
	long long int result = x > y ? x : y;
	long long int denominator = x > y ? y : x;
	long long int i = 1;
	while (result%denominator != 0) {
		i++;
		result = base * i;
	}
	return result;
}
