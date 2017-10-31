#pragma once
#include<Siv3D.hpp>
#include "Bullet.h"

class Player {
	enum Speed {
		HIGHER, SLOWER, COUNT
	} speed;


	int equipWeaponA = 0;
	int equipBulletA = 0;

	int size = 6;
	int power = 10;

	Vec2 position;
	Vec2 velocity;
	double acceleration[Speed::COUNT] = { 0.2, 0.05 };
	double deceleration[Speed::COUNT] = { 0.98, 0.9 };
	Vec2 force;
	double mass = 10.00;

	int shotWait = 8;
	int shotCount = 0;
	Vec2 direction;
	double grouping = 0.1;
	int life = 12000;
	int maxLife = 12000;
	int energy = 10000;
	int maxEnergy = 10000;

	Vec2 UI_position = { 100, 100 };

	std::function<Vec2(const Bullet &)> bullets_move;
	std::function<ShapePattern(Vec2, float)> create_bullets_shape;

public:

	Player();
	~Player();

	void reset();

	void update();
	void update_UI();
	void move();
	void draw();
	void draw_UI();
	void shot();
	void damaged(int damage);

	const Vec2& get_position() const;
	const Vec2& get_direction() const;
	const double get_atan2() const;
	const Circle get_shape() const;
	const int get_power() const;
	const bool killed() const;
};
