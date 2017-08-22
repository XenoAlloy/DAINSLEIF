#include "DrawPattern.h"


void DrawPattern::circle(const Bullet& bullet)
{
	Circle(bullet.position, 6).draw(Color(0, 255, 200, 220));
}

void DrawPattern::quad(const Bullet& bullet)
{
	Quad(
	{ bullet.position.x, bullet.position.y - 8 }, 
	{ bullet.position.x + 4, bullet.position.y + 2 },
	{ bullet.position.x, bullet.position.y + 8 },
	{ bullet.position.x - 4, bullet.position.y + 2 }
	)
		.rotatedAt(bullet.position, bullet.get_angle())
		.draw(Color(0, 255, 200, 220));
}