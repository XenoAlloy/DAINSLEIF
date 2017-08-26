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
	dir = {(Input::KeyD.pressed - Input::KeyA.pressed), (Input::KeyS.pressed - Input::KeyW.pressed)};
	
	force += dir*0.1;

	if (dir.x*dir.y) { position += Vec2{ dir.x * speed, dir.y * speed }*0.71; }
	else { position += Vec2{ dir.x * speed, dir.y * speed }; }



	if (Input::KeyShift.pressed)
	{
		bullets_draw = DrawPattern::circle;
	}
	else {
		bullets_draw = DrawPattern::quad;
	}



	if (Input::KeyShift.pressed + Input::KeySpace.pressed > 1) {
		speedLimit = (slowerSpeed + higherSpeed)*0.5;

	}
	else if (Input::KeyShift.pressed)
	{
		speedLimit = slowerSpeed;
	}
	else if (Input::KeySpace.pressed)
	{
		speedLimit = higherSpeed;
	}
	else
	{
		speedLimit = baseSpeed;
	}




	if (dir.length() > 0)
	{
		dxdy = Vec2{ dir.x * speed, dir.y * speed };

		if (speedLimit > speed) {
			speed += acceleration;
		}
		else 
		{
			speed -= 0.05;
		}
	}
	else {
		if (speed > 0.10)
		{
			speed -= 0.18;
		}
		else {
			speed = 0;
		}
	}

	dxdy = dxdy*0.96;
	if (dxdy.length() <= 1) { dxdy = Vec2{ 0,0 }; }
	position += dxdy;

	


	

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
const double& Player::get_speed() const
{
	return speed;
}
