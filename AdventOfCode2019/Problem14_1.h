#pragma once
#include <vector>
#include <string>
#include <unordered_map>

struct QuantityPair {
	public:
		long long int quantity;
		std::string name;
		QuantityPair(int quantity, std::string name);
		QuantityPair();
};
struct Reaction {
	QuantityPair rhs;
	std::vector<QuantityPair> lhs;
	bool IsPureOre();
};
class Problem14_1
{
public:

	void Solve(std::string fileName);
	Problem14_1();
	~Problem14_1();
	static long long int FindMinAmountForFuel(const std::vector<Reaction> allReactions, long long int fuelNumber);
	static Reaction ReadReaction(std::string line);
};

