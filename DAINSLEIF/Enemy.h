# pragma once
# include <Siv3D.hpp>
class Enemy {
	int life;
	Vec2 position;
	int shapeType;
	int bulletType;
	int moveType;

	std::function<Vec2(const Enemy &)> _move;

public:

	Enemy(std::function<Vec2(const Enemy&)>);
	~Enemy();

	void update();
	void move();
	void draw();
	void shot();
	void damaged(int damage);

	const Vec2 & get_position() const;
};

