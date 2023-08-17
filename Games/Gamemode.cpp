#include "Gamemode.h"

Gamemode::Gamemode()
{
}

void Gamemode::PrintTitle(int y, unsigned short TEXTColor, unsigned short BACKGROUNDColor)
{
	int TitleSize = static_cast<int>(Title.size());
	SetCursorPosition(y - TitleSize / 2, 0);
	Print(Title, TEXTColor, BACKGROUNDColor);
}

void Gamemode::PrintInstructions(int y, unsigned short TEXTColor, unsigned short BACKGROUNDColor)
{
	SetCursorPosition(y*2 + 3, 3);
	Print(Instructions, TEXTColor, BACKGROUNDColor);
}

void Gamemode::Win(int y)
{
	SetCursorPosition(0, y+1);
	Print(MSG_Win, TEXTBrightGreen);
}

void Gamemode::Lose(int y)
{
	SetCursorPosition(0, y+1);
	Print(MSG_Lose, TEXTBrightRed);
}
