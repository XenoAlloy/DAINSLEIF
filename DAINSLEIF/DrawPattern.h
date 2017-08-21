#pragma once
#include "Bullet.h"
#include "Player.h"

class DrawPattern
{
public:
	static void circle(const Bullet&);
	static void quad(const Bullet&);
	//static std::function<(const Bullet&)> DrawPattern::quad(const Player & player);

	DrawPattern() = delete;
	~DrawPattern() = delete;
	DrawPattern(const DrawPattern&) = delete;
	DrawPattern& operator=(const DrawPattern&) = delete;
	DrawPattern(DrawPattern&&) = delete;
	DrawPattern& operator=(DrawPattern&&) = delete;

};

