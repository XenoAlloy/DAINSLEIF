# include "Enemy.h"
# include "Player.h"

Enemy::Enemy(/*Circle,*/std::function<Vec2(const Enemy&)> move_pattern)
	: _move(move_pattern)
	, shape(position, 50)
	, position{ 800, 100 } {
}

Enemy::~Enemy() {
}


void Enemy::update() {
}

void Enemy::move() {
	auto distance = _move(*this);
	position += distance;
	shape.moveBy(distance);
}

void Enemy::draw() {
	shape.draw(Color(255, 0, 0));
}

void Enemy::shot() {
}
void Enemy::damaged(int damage) {
	life -= damage;
}
const Vec2 & Enemy::get_position() const {
	return position;
}
const Circle& Enemy::get_shape() const {
	return shape;
}
const bool Enemy::killed()const {
	return life <= 0;
}
const int Enemy::get_power() const {
	return power;
}