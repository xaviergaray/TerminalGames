#include "CoreMinimum.h"
#include "Actor.h"
#include "Board.h"
#include "Snake.h"
#include <conio.h>

using std::vector;

inline void StartGame(int Selection)
{
	switch (Selection)
	{
	case 1:
	{
		Snake snake(20);
		break;
	}
	case 2:
		
		break;
	case 3:
		
		break;
	}
}

int main()
{
	ShowConsoleCursor(false);
	std::vector<std::string> MainMenu =
	{
		"+------------------+",
		"|Snake             |",
		"|Connect Four      |",
		"|Sudoku            |",
		"+------------------+"
	};

	std::vector<std::string> Instructions =
	{
		"+----------------------------------------------+",
		"|Use UP and DOWN arrow keys to change selection|",
		"|Press ENTER or SPACE to confirm selection     |",
		"|Press ESC to quit                             |",
		"+----------------------------------------------+"
	};

	SetConsoleColor(TEXTBrightGreen);
	Print(MainMenu);

	int SelectionPosition[2] = { 0,1 };
	
	SetCursorPosition(SelectionPosition[0], SelectionPosition[1]);
	Print(MainMenu[SelectionPosition[1]], TEXTDarkGreen, BACKGROUNDGray);
	const int& const SelectionMenuWidth = MainMenu[0].size();
	Loop(Instructions.size(), [&](int& row)
		{
			SetCursorPosition(SelectionMenuWidth, row);
			Print(Instructions[row]);
		});

	bool bGameStarted{ false };

	while (!bGameStarted)
	{	
		//if (!bGameStarted) continue;

		auto ReflectOption = [&]()
			{
				Clamp(SelectionPosition[1], 1, MainMenu.size() - 2);
				SetCursorPosition(0, SelectionPosition[1]);
				Print(MainMenu[SelectionPosition[1]], TEXTDarkGreen, BACKGROUNDGray);
			};

		switch (_getch())
		{
		case KEY_UP:
			SetCursorPosition(0, SelectionPosition[1]);
			Print(MainMenu[SelectionPosition[1]]);
			SelectionPosition[1]--;
			ReflectOption();
			break;
		case KEY_DOWN:
			SetCursorPosition(0, SelectionPosition[1]);
			Print(MainMenu[SelectionPosition[1]]);
			SelectionPosition[1]++;
			ReflectOption();
			break;
		case KEY_SPACE:
			bGameStarted = true;
			StartGame(SelectionPosition[1]);
			break;
		case KEY_ENTER:
			bGameStarted = true;
			StartGame(SelectionPosition[1]);
			break;
		case KEY_ESC:
			goto TerminateProgram;
		}
	}



	TerminateProgram:
	cls();
	SetCursorPosition(0, 0);
	Print("Thank you for playing. Come again!");
}