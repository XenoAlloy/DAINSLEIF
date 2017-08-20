#include "MovePattern.h"


Vec2 MovePattern::straight_up(const Bullet & bullet)
{
	return {0, -3};
}

std::function<Vec2(const Bullet&)> MovePattern::for_mouse(const Player & player)
{
	return [direction=Vec2(), &player](const Bullet & c) mutable {
		if (direction.isZero()) {
			direction = (Mouse::Pos() - player.get_position()).normalize();
		}
		return direction;
	};
}

