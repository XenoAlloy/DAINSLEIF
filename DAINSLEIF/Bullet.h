#pragma once
#include <Siv3D.hpp>
#include "BulletShape.hpp"

class Bullet {
	int life = 1;
	int power = 2;
	Vec2 position;
	Vec2 direction;
	double grouping;
	BulletShape shape;
	std::function<Vec2(const Bullet &)> _move;

public:
	Bullet(Vec2, std::function<Vec2(const Bullet&)>, BulletShape, Vec2 normalized_direction, double grouping);
	~Bullet();

	Bullet& operator=(const Bullet&) = default;

	void update();
	void draw();
	void damaged();

	const bool killed()const;
	const double get_angle() const;
	const BulletShape& get_shape() const;
	const int get_power() const;
};
