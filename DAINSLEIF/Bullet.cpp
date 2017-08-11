#include "Bullet.h"


Bullet::Bullet(Vec2 _position, std::function<Vec2(const Bullet&)> _move_pattern, std::function<void(const Bullet&)> _draw_pattern)
	: position(_position), move(_move_pattern), draw(_draw_pattern) {}


void Bullet::update() {
	position += move(*this);

}


Bullet::~Bullet(){}
