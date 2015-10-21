#pragma once

#include "vec2.hpp"
#include <array>

namespace trek {
namespace math {

class Quadrangle2 {
public:
	using Vertices = std::array<Vec2, 4>;
public:
	Quadrangle2(const Vec2& vtx1, const Vec2& vtx2, const Vec2& vtx3 , const Vec2& vtx4);
	Quadrangle2(Vec2&& vtx1, Vec2&& vtx2, Vec2&& vtx3, Vec2&& vtx4);
	Quadrangle2(const Vertices& vertices);
	Quadrangle2(Vertices&& vertices);

	bool checkPoint(const Vec2& dot) const;

	const Vertices& vertices() const {
		return mVertices;
	}
private:
	Vertices mVertices;
};

}
}
