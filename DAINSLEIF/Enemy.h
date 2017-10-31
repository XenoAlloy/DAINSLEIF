# pragma once
# include <Siv3D.hpp>
class Enemy {
	int life = 10;
	int power = 300;
	Vec2 position;
	Vec2 velocity;
	int shapeType;
	int bulletType;
	int moveType;
	std::function<Vec2(const Enemy &)> _move;
	Circle shape;

public:

	Enemy(Vec2, Vec2, std::function<Vec2(const Enemy&)>);
	~Enemy();


	void update();
	void move();
	void draw();
	void shot();
	void damaged(int damage);

	const Vec2 & get_position() const;
	const Vec2 & get_velocity() const;
	const Circle& get_shape() const;
	const int get_power() const;
	const bool killed()const;
};

