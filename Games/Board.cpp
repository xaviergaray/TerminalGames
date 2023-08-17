#include "Board.h"

Board::Board() : Dim({10,10})
{
	BuildBoard();
}

Board::Board(int Dim) : Dim({Dim, Dim})
{
	BuildBoard();
}

Board::Board(int DimX, int DimY) : Dim({DimX, DimY})
{
	BuildBoard();
}

void Board::BuildBoard()
{
	std::vector<std::string> TempBoard;

	Loop(Dim[1], [&](int& row)
		{
			std::string RowString;

			if (row == 0 || row == Dim[1] - 1)
			{
				RowString.push_back(Corner);
				Loop(Dim[0] * 2 - 2, [&](int& col)
					{
						RowString.push_back(CeilingAndFloor);
					});
				RowString.push_back(Corner);
			}
			else
			{
				RowString.push_back(Wall);
				Loop(Dim[0] * 2 - 2, [&](int& col)
					{
						RowString.push_back(' ');
					});
				RowString.push_back(Wall);
			}

			TempBoard.push_back(RowString);
		});

	BoardMap = TempBoard;
}
