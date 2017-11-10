#include "Bullet.h"




Bullet::Bullet(Vec2 position, std::function<Vec2(const Bullet&)> move_pattern,
	ShapePattern shape, Vec2 normalized_direction, double grouping)
	: position(position), _move(move_pattern),
	shape(shape), direction(normalized_direction), grouping(grouping) {
}

Bullet::~Bullet() {}


void Bullet::update() {
	auto distance = _move(*this);
	position += distance;
	shape.moveBy(distance);
}

void Bullet::draw() {
	shape.draw(Color(0, 255, 200, 220));
}

void Bullet::damaged() {
	life -= 1;
}

const bool Bullet::killed()const {
	return life <= 0 || !shape.intersects(Window::ClientRect());
}

const double Bullet::get_angle() const {
	return atan2(direction.x, -direction.y);
}

const ShapePattern& Bullet::get_shape() const {
	return shape;
}

const int Bullet::get_power()const {
	return power;
}