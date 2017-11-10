# pragma once
# include <Siv3D.hpp>
# include "Enemy.h"

struct EnemyAlert : IEffect {
	Enemy& enemy;
	Circle circle;
	float scale;

	bool update(double) override;
	EnemyAlert(Enemy&, float);
	~EnemyAlert();
};

