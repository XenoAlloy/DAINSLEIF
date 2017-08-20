#pragma once
#include "Bullet.h"
#include "Player.h"

class MovePattern
{
public:
	static Vec2 straight_up(const Bullet&);
	static std::function<Vec2(const Bullet&)> for_mouse(const Player&);

	MovePattern() = delete;
	~MovePattern() = delete;
	MovePattern(const MovePattern&) = delete;
	MovePattern& operator=(const MovePattern&) = delete;
	MovePattern(MovePattern&&) = delete;
	MovePattern& operator=(MovePattern&&) = delete;
};

