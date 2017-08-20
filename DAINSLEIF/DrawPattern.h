#pragma once
#include "Bullet.h"

class DrawPattern
{
public:
	static void circle(const Bullet&);
	static void quad(const Bullet&);

	DrawPattern() = delete;
	~DrawPattern() = delete;
	DrawPattern(const DrawPattern&) = delete;
	DrawPattern& operator=(const DrawPattern&) = delete;
	DrawPattern(DrawPattern&&) = delete;
	DrawPattern& operator=(DrawPattern&&) = delete;

};

