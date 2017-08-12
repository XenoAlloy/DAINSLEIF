#pragma once
#include "Bullet.h"

class MovePattern
{
public:
	static Vec2 straight_up(const Bullet&);


	MovePattern() = delete;
	~MovePattern() = delete;
	MovePattern(const MovePattern&) = delete;
	MovePattern& operator=(const MovePattern&) = delete;
	MovePattern(MovePattern&&) = delete;
	MovePattern& operator=(MovePattern&&) = delete;
};

