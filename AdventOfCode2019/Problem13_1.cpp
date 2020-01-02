#include "pch.h"
#include "Problem13_1.h"
#include "Problem11_1.h"
#include "Problem1_1.h"
#include <iostream>
#include <Windows.h>


Problem13_1::Problem13_1()
{
}


Problem13_1::~Problem13_1()
{
}

void Problem13_1::Solve(std::string fileName)
{
	auto program = Problem1_1::ReadCommaDelimetedDataLong(fileName);
	ComputerWithBreaksEnabled computer;
	int i = 0;
	computer.program.clear();
	for (auto val : program) {
		computer.program[i] = val;
		i++;
	}
	computer.maxPlaceInMemory = program.size();
	auto output = computer.RunProgram(0);
	int score = 0;
	int maxX = 0;
	int maxY = 0;
	auto game = ReadGame(output, score, maxX, maxY);
	int countBlockTiles = 0;
	for (auto tile : game) {
		if (tile.color == 2) {
			countBlockTiles++;
		}
	}
	PrintGame(game,score, maxX, maxY);
	std::cout << countBlockTiles << std::endl;
}

std::vector<Vector2> Problem13_1::ReadGame(std::vector<int64_t> board, int& score, int& maxX, int& maxY)
{
	 std::vector<Vector2> result;
	 for (int i = 0; i < board.size(); i += 3) {
		 if (board[i] == -1 && board[i + 1] == 0) {
			 score = board[i + 2];
		 }
		 else {
			 result.emplace_back(Vector2(board[i], board[i + 1], board[i + 2]));
			 if (board[i] > maxX) {
				 maxX = board[i];
			 }
			 if (board[i + 1] > maxY) {
				 maxY = board[i + 1];
			 }
		 }
	 }

	 return result;
}

std::vector<Vector2> Problem13_1::ReadSomeGame(std::vector<int64_t> board, int & score)
{
	std::vector<Vector2> result;
	for (int i = 0; i < board.size(); i += 3) {
		if (board[i] == -1 && board[i + 1] == 0) {
			score = board[i + 2];
		}
		else {
			result.emplace_back(Vector2(board[i], board[i + 1], board[i + 2]));
		}
	}

	return result;
}

void Problem13_1::PrintGame(std::vector<Vector2> board, int score, int maxX, int maxY)
{
	ClearConsole();
	std::cout <<"SCORE: "<<score<< std::endl;
	int i = 0;
	for (int y = 0; y <= maxY; y++) {
		for (int x = 0; x <= maxX; x++) {
			std::cout << ChooseChar(board[i]);
			i++;
		}
		std::cout << std::endl;
	}
}

char Problem13_1::ChooseChar(Vector2 tile)
{
	switch (tile.color)
	{
	case 0:
		return ' ';
		break;
	case 1:
		return '#';
		break;
	case 2:
		return 'o';
		break;
	case 3:
		return '=';
		break;
	case 4:
		return '@';
		break;
	default:
		break;
	}
}

void Problem13_1::ClearConsole()
{
	char fill = ' ';
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}


