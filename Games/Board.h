#pragma once
#include "CoreMinimum.h"

class Board
{
public:
	Board();
	Board(int Dim);
	Board(int DimX, int DimY);

	inline void SetBoard(std::vector<std::string> BoardMap) { this->BoardMap = BoardMap; }

	inline void SetBoard(int x, int y, char c) { BoardMap[y][x] = c; }

	inline void SetBoard(int row, std::string s) { BoardMap[row] = s; }

	inline void SetBoard(std::vector<int> Coords, char c) { BoardMap[Coords[1]][Coords[0]]; }

	inline std::vector<std::string> GetBoard() const { return BoardMap; }
	
	inline char GetBoard(int x, int y) const { return BoardMap[y][x]; }

	inline char GetBoard(std::vector<int> Coords) const { return BoardMap[Coords[1]][Coords[0]]; }

	inline std::vector<int> GetDimensions() const { return Dim; }


protected:

private:
	const char Corner = '*';
	const char Wall = '|';
	const char CeilingAndFloor = '-';

	std::vector<int> const Dim;

	std::vector<std::string> BoardMap =
	{
		"BOARD NOT SET!"
	};

	void BuildBoard();
};

