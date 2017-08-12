#include "DrawPattern.h"


void DrawPattern::circle(const Bullet& bullet)
{
	Circle(bullet.position, 6).draw(Color(0, 255, 200, 255));
}
