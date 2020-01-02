#include "pch.h"
#include "Problem1_1.h"
#include "Problem14_1.h"
#include <sstream>
#include <iostream>
#include <queue>


void Problem14_1::Solve(std::string fileName)
{
	auto allLines = Problem1_1::ReadAllLines(fileName);
	std::vector<Reaction> allReactions;
	for(auto line : allLines) {
		allReactions.emplace_back(ReadReaction(line));
	}




	
	std::printf("Result: %i \n", FindMinAmountForFuel(allReactions, 1));
}

Problem14_1::Problem14_1()
{
}


Problem14_1::~Problem14_1()
{
}

Reaction Problem14_1::ReadReaction(std::string line)
{
	Reaction result;
	std::string lhs;
	std::string rhs;
	rhs = line.substr(line.find('=') + 3, line.size());
	lhs = line.substr(0, line.find('=') - 1);
	std::stringstream ss(lhs);
	std::string oneReactionLine;
	while (ss.good()) {
		std::getline(ss, oneReactionLine, ',');
		if (oneReactionLine[0] == ' ') {
			oneReactionLine = oneReactionLine.substr(1, oneReactionLine.size());
		}
		result.lhs.emplace_back(QuantityPair(
			std::stoi(oneReactionLine.substr(0, oneReactionLine.find(' '))),
			oneReactionLine.substr(oneReactionLine.find(' ') + 1, oneReactionLine.size())
		));
	}

	result.rhs = QuantityPair(
		std::stoi(rhs.substr(0, rhs.find(' '))),
		rhs.substr(rhs.find(' ') + 1, rhs.size()));
	return result;
}

QuantityPair::QuantityPair(int quantity, std::string name)
{
	this->quantity = quantity;
	this->name = name;
}

QuantityPair::QuantityPair()
{
}



long long int Problem14_1::FindMinAmountForFuel(const std::vector<Reaction> allReactions, long long int fuelNumber)
{
	std::unordered_map<std::string, int> leftoverBag;
	Reaction myReaction;
	long long int result = 0;
	for (int i = 0; i < allReactions.size(); i++) {
		if (allReactions[i].rhs.name == "FUEL") {
			myReaction = allReactions[i];
		}
		else {
			leftoverBag[allReactions[i].rhs.name] = 0;
		}
	}

	myReaction.rhs.quantity *= fuelNumber;
	for (int i = 0; i < myReaction.lhs.size(); i++) {
		myReaction.lhs[i].quantity *= fuelNumber;
	}

	std::queue<QuantityPair> stuffToProduce;

	for (int i = 0; i < myReaction.lhs.size(); i++)
	{
		stuffToProduce.push(myReaction.lhs[i]);
	}

	while (!stuffToProduce.empty()) {
		auto nextReaction = stuffToProduce.front();
		stuffToProduce.pop();
		//std::printf("Producing %i quantity of %s\n", nextReaction.quantity, nextReaction.name.c_str());
		if (nextReaction.name == "ORE") {
			result += nextReaction.quantity;
		}
		else {
			if (leftoverBag[nextReaction.name] < nextReaction.quantity) {
				nextReaction.quantity -= leftoverBag[nextReaction.name];
				leftoverBag[nextReaction.name] = 0;
				for (auto r : allReactions) {
					if (r.rhs.name == nextReaction.name) {
						long long int multiplier = 0;
						while (r.rhs.quantity*multiplier < nextReaction.quantity) {
							multiplier++;
						}
						leftoverBag[nextReaction.name] = r.rhs.quantity*multiplier - nextReaction.quantity;
						//std::printf("Putting %i quantity of %s in bag\n", leftoverBag[nextReaction.name], nextReaction.name.c_str());
						for (auto l : r.lhs) {
							l.quantity *= multiplier;
							stuffToProduce.emplace(l);
						}
					}
				}
			}
			else {
				leftoverBag[nextReaction.name] -= nextReaction.quantity;
			}
		}
	}
	return result;
}

bool Reaction::IsPureOre()
{
	for (auto r : lhs) {
		if (r.name != "ORE") {
			return false;
		}
	}
	return true;
}
