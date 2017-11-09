# pragma once
# include <Siv3D.hpp>
class SpawnNotice {
	int scale;
	Vec2 position;
	int count;
public:
	void draw();
	const bool killed() const;
	SpawnNotice(Vec2, int);
	~SpawnNotice();
};

