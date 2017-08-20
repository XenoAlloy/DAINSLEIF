#include "Player.h"
#include "GameManager.h"
#include "MovePattern.h"
#include "DrawPattern.h"

Player::Player()
	: bullets_move(MovePattern::for_mouse(*this)), bullets_draw(DrawPattern::quad) {}

Player::~Player()
{
}


void Player::move() {
	dir.x = (Input::KeyD.pressed - Input::KeyA.pressed);
	dir.y = (Input::KeyS.pressed - Input::KeyW.pressed);
	position.x += dir.x * 6;
	position.y += dir.y * 6;
	if (Input::KeyShift.pressed == 1) {
		position.x -= dir.x * 4;
		position.y-= dir.y * 4;
	}
	if (position.x > 390-size-4) {position.x = 390 - size - 4;}
	if (position.x < 30 + size + 4) { position.x = 30 + size + 4; }
	if (position.y > 570 - size - 4) { position.y = 570 - size - 4; }
	if (position.y < 30 + size + 4) { position.y = 30 + size + 4; }

}

void Player::draw() {
	Quad(
	{ position.x , position.y - 20 },
	{ position.x + 8 , position.y + 4 },
	{ position.x , position.y + 16 },
	{ position.x - 8 , position.y + 4 }
	).draw(Color(0, 220, 176, 220));
}

void Player::shot() {
	if (Input::MouseL.pressed)
	{
		if (shotCount > shotWait) {
			GameManager::get_instance().bullets.push_back(
				Bullet(position - Vec2{ 0, 16 }, bullets_move, bullets_draw)
			);
			shotCount = 0;
		}
	}
	
}

void Player::update() {
	shotCount += 1;
	Vec2 distance = Mouse::Pos() - position;
	Vec2 direction = distance.normalized();

}

const Vec2& Player::get_position() const
{
	return position;
}
