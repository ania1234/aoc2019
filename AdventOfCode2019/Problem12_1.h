#pragma once

struct Vector3 {
public:
	int x, y, z;
	Vector3(int x, int y, int z);
	Vector3();
	bool operator==(const Vector3& rhs)
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}
	bool operator!=(const Vector3& rhs)
	{
		return (x != rhs.x || y != rhs.y || z != rhs.z);
	}
};
class Moon {
public:
	Vector3 position;
	Moon(int x, int y, int z);
	Vector3 velocity;
	void UpdatePosition();
	void UpdateVelocity(const Moon otherMoon);
	void UpdateVelocityAndOther(Moon* otherMoon);
	void PrintPosition();
	int CalculateEnergy();
};
class Problem12_1
{
public:
	static int Sign(int a, int b);
	void Solve();
	Problem12_1();
	~Problem12_1();
};

