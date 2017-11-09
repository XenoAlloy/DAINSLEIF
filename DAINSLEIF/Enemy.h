# pragma once
# include <Siv3D.hpp>
# include "ShapePattern.hpp"

class Enemy {
	int life = 10;
	int power = 300;
	Vec2 position;
	Vec2 velocity;
	double angle;
	int shapeType;
	int bulletType;
	int moveType;
	std::function<Vec2(const Enemy &)> _move;
	ShapePattern shape;

public:

	Enemy(Vec2, Vec2, std::function<Vec2(const Enemy&)>, std::function<ShapePattern(Vec2, float, float)>);
	Enemy(Vec2, Vec2, std::function<Vec2(const Enemy&)>, ShapePattern, double);
	~Enemy();


	void update();
	void move();
	void draw();
	void shot();
	void damaged(int damage);

	//const int get
	const Vec2 & get_position() const;
	const Vec2 & get_velocity() const;
	const ShapePattern& get_shape() const;
	const int get_power() const;
	const bool killed()const;
};

