#include "pch.h"
#include "Problem1_1.h"
#include "Problem11_1.h"
#include "Problem13_1.h"
#include "Problem13_2.h"
#include <iostream>
#include <sstream>  
#include <SFML/Graphics/Text.hpp>



void Problem13_2::Solve(std::string fileName)
{
	sf::Font myFont;
	myFont.loadFromFile("\\sansation.ttf");
	sf::Text myScore;
	myScore.setFillColor(sf::Color::Magenta);
	myScore.setFont(myFont);
    auto program = Problem1_1::ReadCommaDelimetedDataLong(fileName);
	ComputerWithBreaksEnabled computer;
	int i = 0;
	computer.program.clear();
	for (auto val : program) {
		computer.program[i] = val;
		i++;
	}
	computer.program[0] = 2;
	computer.maxPlaceInMemory = program.size();
	int score = 0;
	int maxX = 0;
	int maxY = 0;
	int joystickMove = 0;
	std::vector<int64_t> gameOutput = computer.RunProgram(0);
	auto game = Problem13_1::ReadGame(gameOutput, score, maxX, maxY);

	sf::RenderWindow window(sf::VideoMode(440,420), "SFML works!");
	wallShape = sf::RectangleShape(sf::Vector2f(10, 10));
	wallShape.setFillColor(sf::Color::Blue);
	ballShape = sf::CircleShape(5);
	ballShape.setFillColor(sf::Color::Green);
	blockShape = sf::CircleShape(5);
	blockShape.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				int joystickMove = 0;
				if (event.key.code == sf::Keyboard::Left) {
					joystickMove = -1;
				}
				if (event.key.code == sf::Keyboard::Right) {
					joystickMove = 1;
				}
				if (event.key.code == sf::Keyboard::Up) {
					joystickMove = BotChooseMove(game);
				}
				computer.input.emplace_back(joystickMove);
				auto correctedOutput = computer.RunProgram(0);
				auto correctedGame = Problem13_1::ReadSomeGame(correctedOutput, score);
				for (auto tile : correctedGame) {
					int tileNumber = tile.x + tile.y*(maxX+1);
					game[tileNumber] = tile;
				}
			}
		}
		window.clear();
		PrintGame(game, score, maxX, maxY, window);
		std::stringstream ss;
		ss << score;
		std::string scoreString;
		ss >> scoreString;
		myScore.setString(scoreString);
		std::cout << scoreString << std::endl;
		window.draw(myScore);
		window.display();

	}
}

void Problem13_2::PrintGame(std::vector<Vector2> board, int score, int maxX, int maxY, sf::RenderWindow &window)
{
	sf::Shape* shape;
	int i = 0;
	for (int y = 0; y <= maxY; y++) {
		for (int x = 0; x <= maxX; x++) {
			shape = ChooseShape(board[i]);
			if (shape != nullptr) {
				window.draw(*shape);
			}
			delete(shape);
			i++;
		}
	}
}

int Problem13_2::ReadNextMove()
{
	char result;
	std::cin >> result;
	switch (result)
	{
	case 'a':
		return -1;
		break;
	case 's':
		return 0;
		break;
	case 'd':
		return 1;
		break;
	default:
		std::cout << "Invalid input" << std::endl;
		return 123;
		break;
	}
}

int Problem13_2::BotChooseMove(std::vector<Vector2> board)
{
	int playerX;
	int ballX;
	int playerY;
	int ballY;
	for (int i = 0; i < board.size(); i++) {
		if (board[i].color == 3) {
			playerX = board[i].x;
			playerY = board[i].y;
		}
		if (board[i].color == 4) {
			ballX = board[i].x;
			ballY = board[i].y;
		}
	}

	if (playerX < ballX) {
		return 1;
	}
	if (playerX > ballX) {
		return -1;
	}
	if (playerY - ballY > 5) {
		return rand() % 3 - 1;
	}
	return 0;
}

sf::Shape* Problem13_2::ChooseShape(Vector2 tile)
{
	sf::Shape* result = nullptr;
	switch (tile.color)
	{
	case 0:
		return nullptr;
		break;
	case 1:
		result = new sf::RectangleShape(wallShape);
		break;
	case 2:
		result = new sf::CircleShape(blockShape);
		break;
	case 3:
		result = new sf::RectangleShape(wallShape);
		break;
	case 4:
		result = new sf::CircleShape(ballShape);
		break;
	default:
		return nullptr;
		break;
	}

	if (result) {
		result->setPosition(tile.x * 10, tile.y * 10);
	}

	return result;
}

Problem13_2::Problem13_2()
{
}


Problem13_2::~Problem13_2()
{
}
