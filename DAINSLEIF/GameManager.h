# pragma once
# include "Bullet.h"
# include "Enemy.h"

class GameManager {
private:
	GameManager() = default;
	~GameManager() = default;

public:
	Array<Bullet> bullets;
	Array<Enemy> enemies;
	int score;

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	static GameManager& get_instance() {
		static GameManager inst;
		return inst;
	}
};