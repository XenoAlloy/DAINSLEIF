# include "Enemy.h"
# include "Player.h"

Enemy::Enemy(std::function<Vec2(const Enemy&)> move_pattern)
	: _move(move_pattern)
	, position{ 800, 100 }
{
}

Enemy::~Enemy()
{
}


void Enemy::update() 
{
}

void Enemy::move() 
{
	position += _move(*this);
}

void Enemy::draw() 
{
	Circle(position,50).draw(Color(255,0,0));
}

void Enemy::shot() 
{
}

void Enemy::damaged(int damage) 
{
}

const Vec2 & Enemy::get_position() const
{
	return position;
}
