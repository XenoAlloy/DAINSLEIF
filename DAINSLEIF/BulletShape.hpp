#pragma once
#include <Siv3D.hpp>

class BulletShape : public Shape
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
	static BulletShape circle(Vec2 position, float angle);
	static BulletShape quad(Vec2 position, float angle);

	template<class ShapeT>
	BulletShape(ShapeT shape) : Shape(shape)
	{
	}

	BulletShape(const BulletShape&) = default;
	BulletShape(BulletShape&&) = default;
	BulletShape& operator=(const BulletShape&) = default;

	template<class ShapeT2>
	bool intersects(const ShapeT2& other) const {
		return resolve_shape([&other](const auto& shape) { return shape.intersects(other); });
	}
};
