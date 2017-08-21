#pragma once
class Enemy
{


public:

	Enemy();
	~Enemy();

	void update();
	void move();
	void draw();
	void shot();
	void damaged(int damage);
};

