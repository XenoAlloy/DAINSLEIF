# include "EnemySpawner.h"
# include "MovePattern.hpp"
# include "ShapePattern.hpp"

EnemySpawner::EnemySpawner(String csvPath, const Vec2& chaseTarget) {
	static std::unordered_map < String, std::function<Vec2(const Enemy &)>> move_map{
		{L"straight", MovePattern::straight<Enemy>()},
		{L"chase", MovePattern::chase<Enemy>(chaseTarget)}
	};

	CSVReader reader{ L"STAGE/" + csvPath };
	if (!reader.isOpened()) {
		throw std::ios_base::failure("CSV�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B");
		return;
	}

	// �w�b�_�s���΂��čs���Ƃɓǂݍ���
	for (auto i = 1u; i < reader.rows; i++) {
		auto time_sec = reader.get<float>(i, 0);
		auto position = reader.get<Vec2>(i, 1);
		auto velocity = reader.get<Vec2>(i, 2);
		auto move_key = reader.get<String>(i, 3);
		auto shape_key = reader.get<String>(i, 4);
		auto scale = reader.get<float>(i, 5);

		auto movePattern = move_map[move_key];
		auto angle = Atan2(velocity.x, velocity.y);
		auto shapePattern = ShapePattern::enemyShapes.find(shape_key)->second;
		auto shape = shapePattern(position, angle, scale);
		// 60fps������
		unsigned int time_frame = time_sec * 60 + 0.5;

		timeLine.emplace_back(SpawnInfo{ time_frame, { position, velocity, movePattern, shape, angle } });
	}
}


EnemySpawner::~EnemySpawner() {
}

/// sortie���Ăяo���O�ɌĂяo���Ă������ƁB
void EnemySpawner::start() {
	startFrame = System::FrameCount();
	current_it = timeLine.begin();
}

Array<Enemy> EnemySpawner::sortie() {
	Array<Enemy> enemies;
	auto frameCount = System::FrameCount() - startFrame;

	for (; current_it != timeLine.end() && current_it->time_frame <= frameCount; current_it++) {
		enemies.emplace_back(current_it->enemy);
	}

	return enemies;
}
