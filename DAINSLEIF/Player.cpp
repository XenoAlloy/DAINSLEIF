#include "Player.h"
#include "GameManager.h"
#include "MovePattern.h"
#include "DrawPattern.h"

Player::Player()
	: bullets_move(MovePattern::straight(*this)), bullets_draw(DrawPattern::quad) {}

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
	{ position.x, position.y - 4 },
	{ position.x + 10, position.y + 3  },
	{ position.x + 12, position.y + 14 },
	{ position.x + 2 , position.y + 6}
	)
		.rotatedAt(position, atan2(direction.x, -direction.y))
		.drawFrame(2, 0, Color(0, 0, 0))
		.draw(Color(0, 255, 200, 220));
	Quad(
	{ position.x, position.y - 4 },
	{ position.x - 10, position.y + 3 },
	{ position.x - 12, position.y + 14 },
	{ position.x - 2 , position.y + 6 }
	)
		.rotatedAt(position, atan2(direction.x, -direction.y))
		.drawFrame(2, 0, Color(0, 0, 0))
		.draw(Color(0, 255, 200, 220));
	Quad(
	{ position.x , position.y - 20 },
	{ position.x + 8 , position.y + 4 },
	{ position.x , position.y + 16 },
	{ position.x - 8 , position.y + 4 }
	)
		.rotatedAt(position, atan2(direction.x,-direction.y))
		.drawFrame(2, 0, Color(0, 0, 0))
		.draw(Color(255, 255, 255, 255));
	Quad(
	{ position.x , position.y - 8 },
	{ position.x + 4 , position.y + 4 },
	{ position.x , position.y + 20 },
	{ position.x - 4 , position.y + 4 }
	)
		.rotatedAt(position, atan2(direction.x, -direction.y))
		.drawFrame(1, 0, Color(0, 0, 0))
		.draw(Color(255, 255, 255, 255));
}

void Player::shot() {
	if (Input::MouseL.pressed)
	{
		if (shotCount > shotWait) {
			GameManager::get_instance().bullets.push_back(
				Bullet(position + direction*16, bullets_move, bullets_draw, direction)
			);
			shotCount = 0;
		}
	}
	
}

void Player::update() {
	shotCount += 1;
	direction = (Mouse::Pos() - position).normalize();
	
}

void Player::damaged(int damage) 
{
	life -= damage;
}

const Vec2& Player::get_position() const
{
	return position;
}
const Vec2& Player::get_direction() const
{
	return direction;
}
const double& Player::get_atan2() const
{
	return atan2(direction.x, -direction.y);
}
