#pragma once
#include<Siv3D.hpp>

class Bullet
{
	int power;
	std::function<Vec2(const Bullet &)> move;

public:
	Bullet(std::function<Vec2(const Bullet&)>);
	~Bullet();
};

