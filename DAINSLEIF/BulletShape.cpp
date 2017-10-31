#include "ShapePattern.hpp"

const std::unordered_map<String, std::function<ShapePattern(Vec2, float)>> ShapePattern::playerBulletShapes{
	{ L"circle",
		[](auto position, auto _) {
			return Circle(position, 6);
		}
	},
	{ L"quad",
		[](auto position, auto angle) {
			return ShapePattern{
				Quad(
					{ position.x, position.y - 8 },
					{ position.x + 4, position.y + 2 },
					{ position.x, position.y + 8 },
					{ position.x - 4, position.y + 2 }
					).rotatedAt(position, angle) };
		}
	}
};
