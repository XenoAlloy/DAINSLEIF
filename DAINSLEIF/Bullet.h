#pragma once
#include <Siv3D.hpp>
#include "BulletShape.hpp"

class Bullet
{
	int power;
	Vec2 position;
	Vec2 direction;
	double grouping;

	BulletShape shape;

	std::function<Vec2(const Bullet &)> _move;


public:
	Bullet(Vec2, std::function<Vec2(const Bullet&)>,
		BulletShape, Vec2 normalized_direction, double grouping);
	~Bullet();

	Bullet& operator=(const Bullet&) = default;

	void update();
	void draw();

	double get_angle() const;
	const BulletShape& get_shape() const;
};
