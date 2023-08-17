#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <map>
#include <Windows.h>

#pragma region Keyboard ASCII Values

#define KEY_A 97
#define KEY_B 98
#define KEY_C 99
#define KEY_D 100
#define KEY_E 101
#define KEY_F 102
#define KEY_G 103
#define KEY_H 104
#define KEY_I 105
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_M 109
#define KEY_N 110
#define KEY_O 111
#define KEY_P 112
#define KEY_Q 113
#define KEY_R 114
#define KEY_S 115
#define KEY_T 116
#define KEY_U 117
#define KEY_V 118
#define KEY_W 119
#define KEY_X 120
#define KEY_Y 121
#define KEY_Z 122
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_ENTER 13

#pragma endregion

#pragma region Text and Background Colors

#define TEXTDarkBlue FOREGROUND_BLUE
#define TEXTBrightBlue FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define TEXTDarkGreen FOREGROUND_GREEN
#define TEXTBrightGreen FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define TEXTDarkRed FOREGROUND_RED
#define TEXTBrightRed FOREGROUND_RED | FOREGROUND_INTENSITY
#define TEXTYellow 0x0006
#define TEXTBlack 0x0000
#define TEXTWhite 0x000F
#define TEXTCyan 0x000B
#define TEXTPurple 0x000D
#define TEXTPeach 0x000E
#define TEXTDefault 0x0007

#define BACKGROUNDDarkBlue BACKGROUND_BLUE
#define BACKGROUNDBrightBlue BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUNDDarkGreen BACKGROUND_GREEN
#define BACKGROUNDBrightGreen BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define BACKGROUNDDarkRed BACKGROUND_RED
#define BACKGROUNDBrightRed BACKGROUND_RED | BACKGROUND_INTENSITY
#define BACKGROUNDYellow 0x0060
#define BACKGROUNDDefault 0x0000
#define BACKGROUNDGray 0x0070

#pragma endregion

inline void cls()
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD Count;
	DWORD CellCount;
	COORD HomeCoords = { 0,0 };

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;
	CellCount = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(hOut, static_cast<WCHAR>(' '), CellCount, HomeCoords, &Count)) return;

	if (!FillConsoleOutputAttribute(hOut, csbi.wAttributes, CellCount, HomeCoords, &Count)) return;

	SetConsoleCursorPosition(hOut, HomeCoords);
}

inline void SetCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(hOut, coord);
}

inline void SetConsoleColor(unsigned short Color)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	SetConsoleTextAttribute(hOut, Color);
}

inline void ShowConsoleCursor(bool bShowFlag)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);
	CursorInfo.bVisible = bShowFlag;
	SetConsoleCursorInfo(hOut, &CursorInfo);
}

template<typename T>
inline void Print(T c, unsigned short TextColor = TEXTDefault, unsigned short BackgroundColor = BACKGROUNDDefault)
{
	SetConsoleColor(TextColor | BackgroundColor);
	std::cout << c;
	std::cout << std::endl;
	SetConsoleColor(TEXTDefault | BACKGROUNDDefault);
}

template<typename T>
inline void Print(std::vector<std::vector<T>> v2, unsigned short TextColor = TEXTDefault, unsigned short BackgroundColor = BACKGROUNDDefault)
{
	for (std::vector<T>& v : v2)
	{
		Print(v);
		std::cout << std::endl;
	}
}

template<typename T>
inline void Print(std::vector<T> v, unsigned short TextColor = TEXTDefault, unsigned short BackgroundColor = BACKGROUNDDefault)
{
	SetConsoleColor(TextColor | BackgroundColor);
	for (T& c : v)
	{
		std::cout << c;
		std::cout << std::endl;
	}
	SetConsoleColor(TEXTDefault | BACKGROUNDDefault);
}

template<typename T>
inline void Loop(int Start, int End, T Function)
{
	if (Start < End)
	{
		for (int i = Start; i < End; i++)
		{
			Function(i);
		}
	}
	else
	{
		for (int i = Start; i >= End; i--)
		{
			Function(i);
		}
	}
}

template<typename T>
inline void Loop(int Iterations, T Function)
{
	for (int i = 0; i < Iterations; i++)
	{
		Function(i);
	}
}

template<typename T, typename Y, typename Z>
inline void Clamp(T& In, Y Min, Z Max)
{
	if (In < Min) In = Min;
	if (In > Max) In = Max;
}

inline int GetRandom(int Min, int Max)
{
	std::random_device rand;
	std::mt19937 rng(rand());
	std::uniform_int_distribution<> dis(Min, Max);

	return dis(rng);
}

//template<typename T = double, typename Y>
//inline T GetRandom(Y Min, Y Max)
//{	
//	std::random_device rand;
//	std::mt19937 rng(rand());
//	std::uniform_real_distribution<Y> dis(Min, Max);
//	T Value = static_cast<T>(dis(rng));
//
//	return Value;
//}