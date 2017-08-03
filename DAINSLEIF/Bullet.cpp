#include "Bullet.h"


//std::function<std::function<Vec2()>(const Bullet&)> _move_pattern‚ğˆø”‚Æ‚·‚éBullet::Bullet
//
//
Bullet::Bullet(std::function<std::function<Vec2()>(const Bullet&)> _move_pattern)
	: move(_move_pattern(*this)) {}



Bullet::~Bullet()
{
}
