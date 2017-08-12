#include "Bullet.h"


Bullet::Bullet(Vec2 position, std::function<Vec2(const Bullet&)> move_pattern, std::function<void(const Bullet&)> draw_pattern)
	: position(position), _move(move_pattern), _draw(draw_pattern) {}

Bullet::~Bullet() {}


void Bullet::update() {
	position += _move(*this);
}

void Bullet::draw()
{
	_draw(*this);
}
