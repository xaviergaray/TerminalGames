#pragma once
#include "Board.h"

class Gamemode
{
public:
	Gamemode();

protected:
	inline void SetTitle(std::string Title) { this->Title = Title; };
	inline void SetInstructions(std::string Instructions) { this->Instructions = Instructions; };
	inline void SetWinMessage(std::string MSG_Win) { this->MSG_Win = MSG_Win; };
	inline void SetLoseMessage(std::string MSG_Lose) { this->MSG_Lose = MSG_Lose; };

	void PrintTitle(int y, unsigned short TEXTColor = TEXTDefault, unsigned short BACKGROUNDColor = BACKGROUNDDefault);
	void PrintInstructions(int y, unsigned short TEXTColor = TEXTDefault, unsigned short BACKGROUNDColor = BACKGROUNDDefault);

	virtual void Win(int y);
	virtual void Lose(int y);

private:
	std::string Title = "Title not set.";
	std::string Instructions = "Instructions not set.";
	std::string MSG_Win = "Congratulations, you've won!";
	std::string MSG_Lose = "Darn, you lost.";
};

