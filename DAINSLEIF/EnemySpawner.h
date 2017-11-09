# pragma once
# include<Siv3D.hpp>
# include "Enemy.h"
# include "SpawnNotice.h"

class EnemySpawner
{
public:
	struct SpawnInfo {
		unsigned int time_frame;
		Enemy enemy;
	};

private:
	unsigned int startFrame;
	Array<SpawnInfo>::iterator current_it;
	Array<SpawnInfo>::iterator current_notice;

public:
	Array<SpawnInfo> timeLine;

	EnemySpawner(String csvPath, const Vec2& chaseTarget);
	~EnemySpawner();

	void start();
	Array<Enemy> sortie();
	Array<SpawnNotice> notify();
};

