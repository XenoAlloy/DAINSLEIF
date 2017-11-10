# include "Enemy.h"
# include "Player.h"

Enemy::Enemy(Vec2 position, Vec2 velocity, std::function<Vec2(const Enemy&)> move_pattern, std::function<ShapePattern(Vec2, float, float)> shape_creator)
	: _move(move_pattern)
	, shape(shape_creator(position, 0, 4))
	, position(position)
	, velocity(velocity)
	, angle(0) {
}

Enemy::Enemy(Vec2 position, Vec2 velocity, std::function<Vec2(const Enemy&)> move_pattern, ShapePattern shape, double angle)
	: _move(move_pattern)
	, shape(shape)
	, position(position)
	, velocity(velocity)
	, angle(angle) {
}

Enemy::~Enemy() {
}


void Enemy::update() {
	score += 1;
}

void Enemy::move() {
	auto distance = _move(*this);
	position += distance;
	shape.moveBy(distance);

	auto newAngle = Atan2(distance.x, distance.y);
	shape.rotateAt(position, angle - newAngle);

	angle = newAngle;
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
const Vec2 & Enemy::get_velocity() const {
	return velocity;
}
const ShapePattern& Enemy::get_shape() const {
	return shape;
}
const bool Enemy::killed()const {
	return life <= 0;
}
const bool Enemy::outOfWindow() const {
	return !shape.intersects(Window::ClientRect());
}
const int Enemy::get_power() const {
	return power;
}
const int Enemy::get_score() const {
	return score;
}