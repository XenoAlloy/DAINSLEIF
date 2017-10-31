#pragma once
#include <Siv3D.hpp>
#include <unordered_map>

class ShapePattern : public Shape
{
	template<class Func>
	auto resolve_shape(const Func& func) const {
		switch (type()) {
		case Shape::Type::Circle: return func(storage.circle);
		case Shape::Type::Quad: return func(*(storage.quad));
		default: throw std::invalid_argument("‘Î‰‚µ‚Ä‚¢‚È‚¢}Œ`‚ğˆµ‚¨‚¤‚Æ‚µ‚Ä‚¢‚Ü‚·B");
		}
	}


public:
	template<class ShapeT>
	ShapePattern(ShapeT shape) : Shape(shape)
	{
	}

	static const std::unordered_map<String, std::function<ShapePattern(Vec2, float)>> playerBulletShapes;
	static const std::unordered_map<String, std::function<ShapePattern(Vec2, float)>> enemyShapes;


	ShapePattern(const ShapePattern&) = default;
	ShapePattern(ShapePattern&&) = default;
	ShapePattern& operator=(const ShapePattern&) = default;

	template<class ShapeT2>
	bool intersects(const ShapeT2& other) const {
		return resolve_shape([&other](const auto& shape) { return shape.intersects(other); });
	}
};
