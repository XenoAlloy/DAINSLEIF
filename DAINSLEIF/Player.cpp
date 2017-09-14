#include "Player.h"
#include "GameManager.h"
#include "MovePattern.h"
#include "DrawPattern.h"

Player::Player()
	: bullets_move(MovePattern::straight(*this))
	, bullets_draw(DrawPattern::quad)
	, position{ 210, 500 }
	, velocity{} {}

Player::~Player()
{
}


void Player::move() {
	auto move_dir = Vec2{};
	if (Input::KeyD.pressed) move_dir.x += 1;
	if (Input::KeyA.pressed) move_dir.x -= 1;
	if (Input::KeyS.pressed) move_dir.y += 1;
	if (Input::KeyW.pressed) move_dir.y -= 1;
	
	if (!move_dir.isZero()) {
		velocity += acceleration[speed] * move_dir.normalize();
	}
	force += move_dir*0.1;


	if (Input::KeyShift.pressed)
	{
		bullets_draw = DrawPattern::circle;
	}
	else {
		bullets_draw = DrawPattern::quad;
	}

	position += velocity;
	velocity *= deceleration[speed];

	if (position.x > 770-size*3-4) {position.x = 770 - size*3 - 4;}
	if (position.x < 30 + size*3 + 4) { position.x = 30 + size*3 + 4; }
	if (position.y > 570 - size*3 - 4) { position.y = 570 - size*3 - 4; }
	if (position.y < 30 + size*3 + 4) { position.y = 30 + size*3 + 4; }
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
	Circle(
		position, size
	)

		.draw(Color(0, 255, 200, (Input::KeyShift.pressed) * 255))
		.drawFrame(1, 0, Color(0, 0, 0, (Input::KeyShift.pressed) * 150));
}

void Player::shot() {
	if (Input::MouseL.pressed)
	{
		if (shotCount > shotWait) {
			GameManager::get_instance().bullets.push_back(
				Bullet(position + direction*16, bullets_move, bullets_draw, direction, grouping)
			);
			shotCount = 0;
		}
	}
	
}

void Player::update() {
	shotCount += 1;

	direction = (Mouse::Pos() - position).normalize();

	if(Input::KeyShift.pressed)
	{
		speed = Speed::SLOWER;
		bullets_draw = DrawPattern::circle;
	}else {
		speed = Speed::HIGHER;
		bullets_draw = DrawPattern::quad;
	}
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
