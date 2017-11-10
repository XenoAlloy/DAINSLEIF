# include "EnemyAlert.h"
# include "GameManager.h"

EnemyAlert::EnemyAlert(Enemy& enemy, float scale)
	: enemy(enemy)
	, circle(enemy.get_position(), scale)
	, scale(scale * 75) {
}

EnemyAlert::~EnemyAlert() {
}

bool EnemyAlert::update(double t) {
	if (t >= 1) {
		GameManager::get_instance().enemies.emplace_back(enemy);
		return false;
	}

	circle.r = scale * (1 - t);
	circle.drawFrame(2, 0, { 255, 0, 0, static_cast<uint32>(t * 255) });

	return true;
}
