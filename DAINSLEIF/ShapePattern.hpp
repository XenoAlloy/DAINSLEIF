#pragma once
#include <Siv3D.hpp>
#include <unordered_map>

class ShapePattern : public Shape {
	template<class Func>
	auto resolve_shape(const Func& func) const {
		switch (type()) {
		case Shape::Type::Circle: return func(storage.circle);
		case Shape::Type::Quad: return func(*(storage.quad));
		case Shape::Type::Polygon: return func(*(storage.polygon));
		default: throw std::invalid_argument("�Ή����Ă��Ȃ��}�`���������Ƃ��Ă��܂��B");
		}
	}


public:
	template<class ShapeT>
	ShapePattern(ShapeT shape) : Shape(shape) {
	}

	static const std::unordered_map<String, std::function<ShapePattern(Vec2, float)>> playerBulletShapes;
	static const std::unordered_map<String, std::function<ShapePattern(Vec2, float, float)>> enemyShapes;

	ShapePattern(const ShapePattern&) = default;
	ShapePattern(ShapePattern&&) = default;
	ShapePattern& operator=(const ShapePattern&) = default;

	template<class ShapeT2>
	bool intersects(const ShapeT2& other) const {
		return resolve_shape([&other](const auto& shape) { return other.intersects(shape); });
	}

	void rotateAt(const Vec2& origin, float angle) {
		switch (type()) {
		case Shape::Type::Quad:
			*this = storage.quad->rotatedAt(origin, angle);
			break;
		case Shape::Type::Polygon:
			*this = storage.polygon->rotatedAt(origin, angle);
			break;
		}
	}
};
