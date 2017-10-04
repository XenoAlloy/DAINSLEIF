#include "BulletShape.hpp"

BulletShape BulletShape::circle(Vec2 position, float angle)
{
	return BulletShape{ Circle(position, 6) };
}

BulletShape BulletShape::quad(Vec2 position, float angle)
{
	return BulletShape{
		Quad(
			{ position.x, position.y - 8 },
			{ position.x + 4, position.y + 2 },
			{ position.x, position.y + 8 },
			{ position.x - 4, position.y + 2 }
		).rotatedAt(position, angle)
	};
}
