#include "pch.h"
#include "Problem12_1.h"
#include <iostream>
#include <vector>

//returns -1 if a<b, 1 if a>b, 0 if a==b
int Problem12_1::Sign(int a, int b)
{
	if (a < b) {
		return -1;
	}
	if (a > b) {
		return 1;
	}

	return 0;
}

void Problem12_1::Solve()
{
	std::vector<Moon> moons;

	moons.emplace_back(Moon(-3, 15, -11));
	moons.emplace_back(Moon(3, 13, -19));
	moons.emplace_back(Moon(-13, 18, -2));
	moons.emplace_back(Moon(6, 0, -1));

	int step = 0;
	while (step < 1000) {
		std::printf("Step: %i\n", step);
		for (int i = 0; i < moons.size(); i++) {
			moons[i].PrintPosition();
		}
		//apply gravity
		for (int i = 0; i < moons.size(); i++) {
			for (int j = 0; j < moons.size(); j++) {
				if (i != j) {
					moons[i].UpdateVelocity(moons[j]);
				}
			}
		}
		//update position
		for (int i = 0; i < moons.size(); i++) {
					moons[i].UpdatePosition();
		}
		step++;
	}
	int result = 0;
	for (int i = 0; i < moons.size(); i++) {
		result += moons[i].CalculateEnergy();
	}
	std::printf("RESULT: %i", result);
}

Problem12_1::Problem12_1()
{
}


Problem12_1::~Problem12_1()
{
}

Moon::Moon(int x, int y, int z)
{
	this->position = Vector3(x, y, z);
}


void Moon::UpdatePosition()
{
	this->position.x += this->velocity.x;
	this->position.y += this->velocity.y;
	this->position.z += this->velocity.z;
}

void Moon::UpdateVelocity(const Moon otherMoon)
{
	this->velocity.x += Problem12_1::Sign(otherMoon.position.x, this->position.x);
	this->velocity.y += Problem12_1::Sign(otherMoon.position.y, this->position.y);
	this->velocity.z += Problem12_1::Sign(otherMoon.position.z, this->position.z);
}

void Moon::UpdateVelocityAndOther(Moon* otherMoon)
{
	int dx = Problem12_1::Sign(otherMoon->position.x, this->position.x);
	int dy = Problem12_1::Sign(otherMoon->position.y, this->position.y);
	int dz = Problem12_1::Sign(otherMoon->position.z, this->position.z);
	this->velocity.x += dx;
	this->velocity.y += dy;
	this->velocity.z += dz;
	otherMoon->velocity.x -= dx;
	otherMoon->velocity.y -= dy;
	otherMoon->velocity.z -= dz;
}

void Moon::PrintPosition()
{
	std::printf("pos=<x= %i, y=%i, z=%i>, vel=<x=%i, y=%i, z=%i>\n",position.x, position.y, position.z ,velocity.x, velocity.y, velocity.z);
}

int Moon::CalculateEnergy()
{
	int pot = (abs(position.x) + abs(position.y) + abs(position.z));
	int kin = (abs(velocity.x) + abs(velocity.y) + abs(velocity.z));
	return pot * kin;
}

Vector3::Vector3(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}
