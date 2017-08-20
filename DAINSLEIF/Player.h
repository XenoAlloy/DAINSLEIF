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
	Vec2 distance;
	Vec2 direction;

	std::function<Vec2(const Bullet &)> bullets_move;
	std::function<void(const Bullet &)> bullets_draw;

public:

	Player();
	~Player();

	void update();
	void move();
	void draw();
	void shot();
};
