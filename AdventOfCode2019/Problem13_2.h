#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
class Problem13_2
{
public:
	void Solve(std::string fileName);
	void PrintGame(std::vector<Vector2> board, int score, int maxX, int maxY, sf::RenderWindow &window);
	int ReadNextMove();
	int BotChooseMove(std::vector<Vector2> board);
	sf::Shape* ChooseShape(Vector2 board);
	Problem13_2();
	~Problem13_2();
private:
	sf::RectangleShape wallShape;
	sf::CircleShape blockShape;
	sf::CircleShape ballShape;
};

