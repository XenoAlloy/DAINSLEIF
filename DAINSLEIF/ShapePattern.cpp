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
				).rotatedAt(position, angle)
			};
		}
	}
};

const std::unordered_map<String, std::function<ShapePattern(Vec2, float, float)>> ShapePattern::enemyShapes{
	{ L"circle",
		[](auto position, auto angle, auto scale) {
			return ShapePattern{
				Circle(position,10 * scale)
			};
		}
	},
	{ L"square",
			[](auto position, auto angle, auto scale) {
			return ShapePattern{
				Quad{
					{ position.x, position.y - 6 * scale },
					{ position.x + 6 * scale, position.y },
					{ position.x, position.y + 6 * scale },
					{ position.x - 6 * scale, position.y }
				}.rotatedAt(position, angle)
			};
		}
	},
	{ L"wedge",
			[](auto position, auto angle, auto scale) {
			return ShapePattern{
				Polygon{
					{ position.x, position.y - 6 * scale },
					{ position.x + 6 * scale, position.y - 2 * scale },
					{ position.x + 2 * scale, position.y },
					{ position.x, position.y + 4 * scale },
					{ position.x - 2 * scale, position.y },
					{ position.x - 6 * scale, position.y - 2 * scale }
				}.rotatedAt(position, angle)
			};
		}
	}
};