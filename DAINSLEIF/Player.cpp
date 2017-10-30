# include "Player.h"
# include "GameManager.h"
# include "MovePattern.hpp"
# include "BulletShape.hpp"

Player::Player()
	: position{ 400, 500 }
	, create_bullets_shape(BulletShape::quad)
	, bullets_move{ MovePattern::straightForMouse<Bullet>(position) }
	, velocity{} {
}

Player::~Player() {
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

	position += velocity;
	velocity *= deceleration[speed];

	if (position.x > 770 - size * 3 - 4) { position.x = 770 - size * 3 - 4; }
	if (position.x < 30 + size * 3 + 4) { position.x = 30 + size * 3 + 4; }
	if (position.y > 570 - size * 3 - 4) { position.y = 570 - size * 3 - 4; }
	if (position.y < 30 + size * 3 + 4) { position.y = 30 + size * 3 + 4; }
}

void Player::draw() {
	Quad(
	{ position.x, position.y - 4 },
	{ position.x + 10, position.y + 3 },
	{ position.x + 12, position.y + 14 },
	{ position.x + 2 , position.y + 6 }
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
		.rotatedAt(position, atan2(direction.x, -direction.y))
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
void Player::draw_UI() {
	//UI_EN
	FontAsset(L"overDrive6")(L"EN:", energy, L"/", maxEnergy)
		.draw(UI_position + Vec2{ 46, -60 }, Color(255 - 255 * ((double)energy / maxEnergy), 0, 0));
	Line(UI_position + Vec2{ 0, -40 }, UI_position + Vec2{ 30 + 200 * ((double)energy / maxEnergy) , -40 })
		.draw(10, Color(0, 0, 0));
	//UI_AP
	Circle(UI_position, 60)
		.draw(Color(0, 0, 0));
	Circle(UI_position, 60)
		.drawFrame(2, 4, Color(0, 0, 0))
		.drawPie(0.0, -2.0*Pi*((double)life / maxLife), Color(255 - 255 * ((double)life / maxLife), 255 * ((double)life / maxLife), 200 * ((double)life / maxLife)));
	Circle(UI_position, 40)
		.draw(Color(255, 255, 255));
	FontAsset(L"overDrive6")(L"  AP\n", life)
		.drawCenter(UI_position, Color(0, 0, 0));
}
void Player::shot() {
	if (Input::MouseL.pressed) {
		if (shotCount > shotWait) {
			if (energy >= 300 - 150 * Input::KeyShift.pressed) {
				auto bulletPosition = position + direction * 16;
				GameManager::get_instance().bullets.push_back(
					Bullet(
						bulletPosition,
						bullets_move,
						create_bullets_shape(bulletPosition, static_cast<float>(atan2(direction.x, -direction.y))),
						direction,
						grouping
					)
				);
				if (!Input::KeyShift.pressed) {
					GameManager::get_instance().bullets.push_back(
						Bullet(
							bulletPosition,
							bullets_move,
							create_bullets_shape(bulletPosition, static_cast<float>(atan2(direction.x, -direction.y))),
							direction,
							grouping
						)
					);
					energy -= 150;
				}
				energy -= 150;
				shotCount = 0;
			}
		}
	}
}
void Player::update() {
	shotCount += 1;
	direction = (Mouse::Pos() - position).normalize();
	if (Input::KeyShift.pressed) {
		speed = Speed::SLOWER;
		create_bullets_shape = BulletShape::circle;
		energy += 10;
	}
	else {
		speed = Speed::HIGHER;
		create_bullets_shape = BulletShape::quad;
	}
	energy += 5;
	if (energy >= maxEnergy) {
		energy = maxEnergy;
	}
}
void Player::update_UI() {

}
void Player::damaged(int damage) {
	life -= damage;
}
const bool Player::killed() const {
	return life <= 0;
}
const Vec2& Player::get_position() const {
	return position;
}
const Vec2& Player::get_direction() const {
	return direction;
}
const double Player::get_atan2() const {
	return atan2(direction.x, -direction.y);
}
const Circle Player::get_shape() const {
	return Circle(position, size);
}
const int Player::get_power()const {
	return power;
}
