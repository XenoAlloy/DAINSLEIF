#pragma once
#include<Siv3D.hpp>

class Bullet
{
	int power;
	Vec2 position;
	Vec2 direction;
	double grouping;
	
	std::function<Vec2(const Bullet &)> _move;
	std::function<void(const Bullet &)> _draw;
	
	friend class MovePattern;
	friend class DrawPattern;

public:
	Bullet(Vec2, std::function<Vec2(const Bullet&)>, std::function<void(const Bullet&)>, Vec2 normalized_direction, double grouping);
	~Bullet();

	void update();
	void draw();

	double get_angle() const;
};

