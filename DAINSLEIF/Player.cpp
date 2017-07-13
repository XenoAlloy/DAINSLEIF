#include "Player.h"
#include "GameManager.h"


Player::Player()
{


}


Player::~Player()
{
}
void Player::update_move() {
	int DirX(Input::KeyRight.pressed - Input::KeyLeft.pressed);
	int DirY(Input::KeyDown.pressed - Input::KeyUp.pressed);
	PositionX += DirX * 6;
	PositionY += DirY * 6;
	if (Input::KeyShift.pressed == 1) {
		PositionX -= DirX * 4;
		PositionY -= DirY * 4;
	}


}

void Player::draw() {
	Triangle(
	{ PositionX , PositionY - 60 },
	{ PositionX + 40 , PositionY + 20 },
	{ PositionX - 40 , PositionY + 20 }
	).draw(Color(0, 255, 200, 255));
}

void Player::shot() {
	GameManager::get_instance().bullets.push_back(Bullet([]() { return [](Bullet c) {return Vec2(); }; }));
}