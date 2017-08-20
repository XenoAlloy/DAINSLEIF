#include "MovePattern.h"


Vec2 MovePattern::straight_up(const Bullet & bullet)
{
	return {0, -8};
}


std::function<Vec2(const Bullet&)> MovePattern::straight(const Player & player)
{
	return [direction=Vec2(), &player](const Bullet & c) mutable {
		if (direction.isZero()) {
			direction = (Mouse::Pos() - player.get_position()).normalize();
		}
		return direction*8;
	};
}
