#pragma once
#include<Siv3D.hpp>
#include "Bullet.h"

class Player
{
	Vec2 position = {210,500};
	int EquipWeaponA = 0;
	int EquipBulletA = 0;
	int Speed = 6;
	int ShiftDownSpeed = 4;
	int DirX;
	int DirY;
	int Size = 6;

	std::function<Vec2(const Bullet &)> bullets_move;
	std::function<void(const Bullet &)> bullets_draw;

public:

	Player();
	~Player();

	void update_status();
	void move();
	void draw();
	void shot();
};
