#include "Player.h"
#include "GameManager.h"
#include "MovePattern.h"
#include "DrawPattern.h"

Player::Player()
	: bullets_move(MovePattern::straight_up), bullets_draw(DrawPattern::circle) {}

Player::~Player()
{
}


void Player::update_move() {
	int DirX(Input::KeyD.pressed - Input::KeyA.pressed);
	int DirY(Input::KeyS.pressed - Input::KeyW.pressed);
	position.x += DirX * 6;
	position.y += DirY * 6;
	if (Input::KeyShift.pressed == 1) {
		position.x -= DirX * 4;
		position.y-= DirY * 4;
	}
	if (position.x > 390-Size-4) {position.x = 390 - Size - 4;}
	if (position.x < 30 + Size + 4) { position.x = 30 + Size + 4; }
	if (position.y > 570 - Size - 4) { position.y = 570 - Size - 4; }
	if (position.y < 30 + Size + 4) { position.y = 30 + Size + 4; }

}

void Player::draw() {
	Quad(
	{ position.x , position.y - 20 },
	{ position.x + 8 , position.y + 4 },
	{ position.x , position.y + 16 },
	{ position.x - 8 , position.y + 4 }
	).draw(Color(0, 255, 200, 255));
}

void Player::shot() {
	if (Input::KeySpace.pressed)
	{
		GameManager::get_instance().bullets.push_back(
			Bullet(position - Vec2{0, 16}, bullets_move, bullets_draw)
		);
	}
	
}