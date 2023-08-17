#pragma once
#include "CoreMinimum.h"

enum class Direction
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};

class Actor
{
public:
	Actor();

	inline void SetPosition(int x, int y) { Position[0] = x; Position[1] = y; }

	inline void SetPosition(std::vector<int> Coordinates) { Position = Coordinates; }

	inline std::vector<int> GetPosition() const { return Position; }

	inline void SetBody(char c) { Body = { {c} }; }

	inline void SetBody(std::string s) { Body = { s }; }

	inline void SetBody(std::vector<std::string> v) { Body = v; }

	inline std::vector<std::string> GetBody() const { return Body; }

	virtual void Move(Direction Dir);

protected:

private:
	std::vector<int> Position;
	std::vector<std::string> Body;
};

