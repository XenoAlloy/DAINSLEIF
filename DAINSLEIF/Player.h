#pragma once
#include<Siv3D.hpp>
#include "Bullet.h"

class Player
{
	Vec2 position = {210,500};
	Vec2 dir;
	int equipWeaponA = 0;
	int equipBulletA = 0;
	int speed = 6;
	int shiftDownSpeed = 4;
	int size = 6;
	int shotWait = 4;
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
	const Vec2& get_direction() const;
	const double& get_atan2() const;
};
