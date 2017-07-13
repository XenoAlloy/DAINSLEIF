#pragma once
#include "Bullet.h"

class GameManager {
private:
	GameManager() = default;
	~GameManager() = default;

public:
	Array<Bullet> bullets;

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	static GameManager& get_instance() {
		static GameManager inst;
		return inst;
	}
};