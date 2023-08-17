#include "Snake.h"
#include "CoreMinimum.h"
#include <conio.h>
#include <time.h>

Snake::Snake()
{
	Board board;
	StartGame(board);
}

Snake::Snake(int Dim)
{
	Board board(Dim);
	StartGame(board);
}

Snake::Snake(int DimX, int DimY)
{
	Board board(DimX, DimY);
	StartGame(board);
}

void Snake::FasterTimeout(int& Timeout)
{
	Timeout = 250 - Score*10;
	Clamp(Timeout, 70, 300);
}

inline void Snake::PrintScore(int DimX)
{
	SetCursorPosition(DimX*2 + 3, 5);
	Print("Score: ");
	SetCursorPosition(DimX * 2 + 10, 5);
	Print(Score);
}

void Snake::StartGame(Board& board)
{
	cls();
	SetTitle(Title);
	SetInstructions(Instructions);
	PrintTitle(board.GetDimensions()[0], TEXTBrightGreen);
	PrintInstructions(board.GetDimensions()[0]);

	SetCursorPosition(0, 1);
	Print(board.GetBoard());
	PrintScore(board.GetDimensions()[0]);

	Food.SetBody('@');
	PrevDirection = KEY_W;
	
	Player.BodyPositions[0] = { board.GetDimensions()[0], board.GetDimensions()[1] / 2 };
	SpawnFood(board);
	Score = 0;

	SetCursorPosition(0, board.GetDimensions()[1] + 1);
	Print("Press any W, A, S, or D to start...");
	while (!_kbhit());
	SetCursorPosition(0, board.GetDimensions()[1] + 1);
	Print("                                   ");
	UpdateBoardAndUI(board);
	RunningLoop(board) ? Win(board.GetDimensions()[1]) : Lose(board.GetDimensions()[1]);
}

void Snake::UpdateBoardAndUI(Board& board)
{
	if (Score >= 1)
	Loop(Score, 1, [&](int part)
		{
			board.SetBoard(Player.BodyPositions[part][0], Player.BodyPositions[part][1], Player.BodySymbol);
		});
	board.SetBoard(Player.BodyPositions[0][0], Player.BodyPositions[0][1], Player.HeadSymbol);
	SetCursorPosition(0, 1);
	Print(board.GetBoard());
}

void Snake::Eat(Board& board)
{
	Score++;
	Player.BodyPositions[Score] = Player.BodyPositions[Score-1];
	PrintScore(board.GetDimensions()[0]);

	if (Score < 2)
	{
		switch (Dir)
		{
		case Direction::UP:
			Player.BodyPositions[Score][1]++;
			break;
		case Direction::LEFT:
			Player.BodyPositions[Score][0]++;
			break;
		case Direction::RIGHT:
			Player.BodyPositions[Score][0]--;
			break;
		case Direction::DOWN:
			Player.BodyPositions[Score][1]--;
			break;
		}
	} 
	else
	{
		const int& PrevX = Player.BodyPositions[Score - 1][0];
		const int& PrevY = Player.BodyPositions[Score - 1][1];

		const int& PrevX2 = Player.BodyPositions[Score - 2][0];
		const int& PrevY2 = Player.BodyPositions[Score - 2][1];

		int& CurrX = Player.BodyPositions[Score][0];
		int& CurrY = Player.BodyPositions[Score][1];

		if (PrevX != PrevX2)
		{
			PrevX > PrevX2 ? CurrX++ : CurrX--;
		}
		else
		{
			PrevY > PrevY2 ? CurrY++ : CurrY--;
		}
	}

	Clamp(Player.BodyPositions[Score][0], 1, board.GetDimensions()[0]*2 - 2);
	Clamp(Player.BodyPositions[Score][1], 1, board.GetDimensions()[1] - 1);

	SpawnFood(board);
}

void Snake::SpawnFood(Board& board)
{

	std::vector<int> PreviousCoordinates = Food.GetPosition();
	Food.SetPosition(GetRandom(1, board.GetDimensions()[0]), GetRandom(1, board.GetDimensions()[1]-1));
	if (board.GetBoard(Food.GetPosition()) != ' ') SpawnFood(board);
	board.SetBoard(Food.GetPosition()[0], Food.GetPosition()[1], Food.GetBody()[0][0]);
}

bool Snake::RunningLoop(Board& board)
{
	int TimeoutMS = 250;
	int CurrDirection = PrevDirection;
	while (true)
	{
		FasterTimeout(TimeoutMS);
		clock_t StartTime = clock();
		while ((clock() - StartTime) / static_cast<clock_t>(TimeoutMS) < 1)
		{
			if (_kbhit())
			{
				CurrDirection = _getch();
				break;
			}
		}

		switch (CurrDirection)
		{
		case KEY_W:
		case KEY_UP:
			board.SetBoard(Player.BodyPositions[Score][0], Player.BodyPositions[Score][1], ' ');
			Player.Move(Dir = Direction::UP);
			PrevDirection = KEY_W;
			break;

		case KEY_A:
		case KEY_LEFT:
			board.SetBoard(Player.BodyPositions[Score][0], Player.BodyPositions[Score][1], ' ');
			Player.Move(Dir = Direction::LEFT);
			PrevDirection = KEY_A;
			break;

		case KEY_S:
		case KEY_DOWN:
			board.SetBoard(Player.BodyPositions[Score][0], Player.BodyPositions[Score][1], ' ');
			Player.Move(Dir = Direction::DOWN);
			PrevDirection = KEY_S;
			break;

		case KEY_D:
		case KEY_RIGHT:
			board.SetBoard(Player.BodyPositions[Score][0], Player.BodyPositions[Score][1], ' ');
			Player.Move(Dir = Direction::RIGHT);
			PrevDirection = KEY_D;
			break;

		case KEY_ESC:
			return false;
		}

		const char NewPositionSymbol = board.GetBoard(Player.BodyPositions[0][0], Player.BodyPositions[0][1]);
		
		if (NewPositionSymbol != ' ')
		{
			if (NewPositionSymbol == Food.GetBody()[0][0])
			{
				Eat(board);
			}
			else
			{
				return false;
			}
			
		}

		UpdateBoardAndUI(board);
	}

	return false;
}

void Snake::SnakePlayer::Move(Direction Dir)
{
	if (BodyPositions.size() > 1)
	{
		Loop(BodyPositions.size(), 1, [&](int part)
			{
				BodyPositions[part] = BodyPositions[part - 1];
			});
	}

	int& HeadX = BodyPositions[0][0];
	int& HeadY = BodyPositions[0][1];

	switch (Dir)
	{
	case Direction::UP:
		HeadSymbol = '^';
		HeadY--;
		break;
	case Direction::LEFT:
		HeadSymbol = '<';
		HeadX--;
		break;
	case Direction::RIGHT:
		HeadSymbol = '>';
		HeadX++;
		break;
	case Direction::DOWN:
		HeadSymbol = 'v';
		HeadY++;
		break;
	}
}
