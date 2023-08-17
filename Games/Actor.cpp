#include "Actor.h"

Actor::Actor() 
	: Position({ 0,0 }), Body('*')
{
}

void Actor::Move(Direction Dir)
{
	switch (Dir)
	{
	case Direction::UP:
		Position[1]--;
		break;
	case Direction::LEFT:
		Position[0]--;
		break;
	case Direction::DOWN:
		Position[1]++;
		break;
	case Direction::RIGHT:
		Position[0]++;
		break;
	}
}