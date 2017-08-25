#include "MovePattern.h"
#include "Siv3D.hpp"


Vec2 MovePattern::straight_up(const Bullet & bullet)
{
	return {0, -8};
}


std::function<Vec2(const Bullet&)> MovePattern::straight(const Player & player)
{
	return[direction = Vec2(), &player](const Bullet & c) mutable {
		if (direction.isZero()) {
			direction = (Mouse::Pos() - player.get_position()).normalize() + Vec2{ Random(-0.1,0.1), Random(-0.1,0.1) };
		}

		return direction *14;
	};
}
