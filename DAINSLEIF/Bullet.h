#pragma once
#include<Siv3D.hpp>

class Bullet
{
	

	int power;
	std::function<Vec2(const Bullet &)> move;
	

public:
	Vec2 position;

	void update();
	std::function<void(const Bullet &)> draw;
	Bullet(Vec2, std::function<Vec2(const Bullet&)>, std::function<void(const Bullet&)>);
	~Bullet();
};

