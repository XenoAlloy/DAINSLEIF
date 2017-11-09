# pragma once
# include<Siv3D.hpp>
# include "Enemy.h"

class EnemySpawner
{
public:
	struct SpawnInfo {
		unsigned int time_frame;
		Enemy enemy;
		float scale;
	};

private:
	unsigned int startFrame;
	Array<SpawnInfo>::iterator current_it;

public:
	Array<SpawnInfo> timeLine;

	EnemySpawner(String csvPath, const Vec2& chaseTarget);
	~EnemySpawner();

	void start();
	void sortie();
};

