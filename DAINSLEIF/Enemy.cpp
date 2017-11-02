# include "Enemy.h"
# include "Player.h"

Enemy::Enemy(Vec2 position, Vec2 velocity, std::function<Vec2(const Enemy&)> move_pattern, std::function<ShapePattern(Vec2, float, float)> shape_creator)
	: _move(move_pattern)
	, shape(shape_creator(position, 0, 4))
	, position(position)
	, velocity(velocity) {
}

Enemy::Enemy(Vec2 position, Vec2 velocity, std::function<Vec2(const Enemy&)> move_pattern, ShapePattern shape)
	: _move(move_pattern)
	, shape(shape)
	, position(position)
	, velocity(velocity) {
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
const Vec2 & Enemy::get_velocity() const
{
	return velocity;
}
const ShapePattern& Enemy::get_shape() const {
	return shape;
}
const bool Enemy::killed()const {
	return life <= 0;
}
const int Enemy::get_power() const {
	return power;
}