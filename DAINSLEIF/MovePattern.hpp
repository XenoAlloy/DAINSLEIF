# pragma once
# include "Bullet.h"
# include "Player.h"
# include "Enemy.h"

class MovePattern {
public:
	template<class Moving>
	static auto straightForMouse(const Vec2 & from) {
		return[direction = Vec2(), &from](const Moving &) mutable->Vec2 {
			if (direction.isZero()) {
				direction = (Mouse::Pos() - from).normalize() + Vec2{ Random(-0.1,0.1), Random(-0.1,0.1) };
			}

			return direction * 14;
		};
	}

	template<class Moving>
	static auto chase(const Vec2 & target) {
		return [&target](const Moving & m) mutable -> Vec2 {
			return (target - m.get_position()).normalize() * 4;
		};
	}

	MovePattern() = delete;
	~MovePattern() = delete;
	MovePattern(const MovePattern&) = delete;
	MovePattern& operator=(const MovePattern&) = delete;
	MovePattern(MovePattern&&) = delete;
	MovePattern& operator=(MovePattern&&) = delete;
};
