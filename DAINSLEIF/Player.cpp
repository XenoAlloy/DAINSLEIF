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
	if (PositionX > 390-Size-4) {PositionX = 390 - Size - 4;}
	if (PositionX < 30 + Size + 4) { PositionX = 30 + Size + 4; }
	if (PositionY > 570 - Size - 4) { PositionY = 570 - Size - 4; }
	if (PositionY < 30 + Size + 4) { PositionY = 30 + Size + 4; }

}

void Player::draw() {
	Quad(
	{ PositionX , PositionY - 20 },
	{ PositionX + 8 , PositionY + 4 },
	{ PositionX , PositionY + 16 },
	{ PositionX - 8 , PositionY + 4 }
	).draw(Color(0, 255, 200, 255));
}

void Player::shot() {

	GameManager::get_instance().bullets.push_back(Bullet( [](Bullet c){ return Vec2(); } ));
}