#pragma once
#include<Siv3D.hpp>

class Bullet
{
	int power;
	std::function<Vec2()> move;

public:
	Bullet(std::function<std::function<Vec2()>(const Bullet&)>);
	~Bullet();
};

