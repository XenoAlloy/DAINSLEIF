#pragma once
#include<Siv3D.hpp>
#include "Bullet.h"

class Player
{

	enum Speed {
		HIGHER, SLOWER, COUNT
	} speed;

	Vec2 position;
	Vec2 velocity;
	int equipWeaponA = 0;
	int equipBulletA = 0;

	double acceleration[Speed::COUNT] = { 0.2, 0.15 };
	double deceleration[Speed::COUNT] = { 0.98, 0.94 };

	int size = 6;
	int shotWait = 8;
	int shotCount = 0;
	Vec2 direction;
	double grouping = 0.1;
	int life;
	int maxLife;

	std::function<Vec2(const Bullet &)> bullets_move;
	std::function<void(const Bullet &)> bullets_draw;

public:

	Player();
	~Player();

	void update();
	void move();
	void draw();
	void shot();
	void damaged(int damage);

	const Vec2& get_position() const;
	const Vec2& get_velocity() const;
	const Vec2& get_direction() const;
	const double& get_atan2() const;
};
