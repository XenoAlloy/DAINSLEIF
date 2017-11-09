# include "SpawnNotice.h"
SpawnNotice::SpawnNotice(Vec2 position, int scale)
	: position(position)
	, scale(scale)
	, count(60) {
}
SpawnNotice::~SpawnNotice() {
}

void SpawnNotice::draw() {
	Circle(position, (10 * scale + 4) *(60 - count) / 60).drawFrame(2, 0, Color(255, 0, 0, 240 + count * 4 - 240));
	count -= 2;
}
const bool SpawnNotice::killed() const {
	return count <= 0;
}
