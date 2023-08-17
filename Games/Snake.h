#pragma once
#include "Gamemode.h"
#include "Character.h"
#include <map>

class Snake : public Gamemode
{
public:
	Snake();
	Snake(int Dim);
	Snake(int DimX, int DimY);

private:
	struct SnakePlayer : Character
	{
		std::map<int, std::vector<int>> BodyPositions;
		const char BodySymbol = '*';
		char HeadSymbol = '^';
		virtual void Move(Direction Dir) override;
	};

	inline void PrintScore(int DimX);

	SnakePlayer Player;
	Actor Food;
	Direction Dir;

	void StartGame(Board& board);
	void UpdateBoardAndUI(Board& board);
	void Eat(Board& board);
	void SpawnFood(Board& board);
	void FasterTimeout(int& Timeout);

	int Score;
	int PrevDirection;

	std::string const Title = "Snake";
	std::string const Instructions = "Use WASD to move your snake towards the food!";

	bool RunningLoop(Board& board);
};

