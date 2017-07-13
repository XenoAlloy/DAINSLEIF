#pragma once
#include<Siv3D.hpp>

class Player
{
	int EquipWeaponA = 0;
	int EquipBulletA = 0;
	int Speed = 6;
	int ShiftDownSpeed = 4;
	int PositionX = 230;
	int PositionY = 500;
	int DirX;
	int DirY;

public:

	Player();
	~Player();

	void update_status();
	void update_move();
	void draw();
	void shot();
};
