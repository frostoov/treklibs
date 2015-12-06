#include "quadrangle2.hpp"

#include <cmath>

namespace trek {
namespace math {

using std::move;
using std::vector;
using std::domain_error;

Quadrangle2::Quadrangle2(const Vec2& vtx1, const Vec2& vtx2, const Vec2& vtx3, const Vec2& vtx4)
	: mVertices{{vtx1, vtx2, vtx3, vtx4}} { }

Quadrangle2::Quadrangle2(Vec2&& vtx1, Vec2&& vtx2, Vec2&& vtx3, Vec2&& vtx4)
	: mVertices{{move(vtx1), move(vtx2), move(vtx3), move(vtx4) }} { }

Quadrangle2::Quadrangle2(const Vertices& vertices)
	: mVertices(vertices) { }

Quadrangle2::Quadrangle2(Quadrangle2::Vertices&& vertices)
	: mVertices(move(vertices)) { }

bool Quadrangle2::hasPoint(const Vec2 &point) const {
	Vec2 center((mVertices[0] + mVertices[1] + mVertices[2] + mVertices[3]) * 0.25);
	for(int k = 0 ; k < 4; ++k) {
		int l = k + 1;
		if(l == 4)
			l = 0;
		auto norm = Vec2(
			mVertices[l].y - mVertices[k].y,
			mVertices[k].x - mVertices[l].x
		).ort();
		auto C = norm * mVertices[k];
		auto distDot = norm * point - C;
		auto distCen = norm * center - C;
		if(distDot * distCen < 0)
			return false;
	}
	return true;
}

}
}
