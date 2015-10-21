#include "quadrangle2.hpp"

#include <cmath>

namespace trek {
namespace math {

using std::move;

Quadrangle2::Quadrangle2(const Vec2& vtx1, const Vec2& vtx2, const Vec2& vtx3, const Vec2& vtx4)
	: mVertices{{vtx1, vtx2, vtx3, vtx4}} { }

Quadrangle2::Quadrangle2(Vec2&& vtx1, Vec2&& vtx2, Vec2&& vtx3, Vec2&& vtx4)
	: mVertices{{move(vtx1), move(vtx2), move(vtx3), move(vtx4) }} { }

Quadrangle2::Quadrangle2(const Vertices& vertices)
	: mVertices(vertices) { }

Quadrangle2::Quadrangle2(Quadrangle2::Vertices&& vertices)
	: mVertices(move(vertices)) { }

bool Quadrangle2::checkPoint(const Vec2& point) const {
	Vec2 cen((mVertices[0] + mVertices[1] + mVertices[2] + mVertices[3]) * 0.25);
	for(int k = 0, l = 1 ; k < 4; ++k, ++l) {
		if(l == 4)
			l = 0;
		auto norm = Vec2(
		                mVertices[l].y() - mVertices[k].y(),
		                mVertices[k].x() - mVertices[l].x()
		            ).ort();
		auto C = norm * mVertices[k];
		auto distDot = norm * point - C;
		auto distCen = norm * cen - C;
		if(/* distDot - distCen > 0e-10 && */ distDot * distCen < 0)
			return false;
	}
	return true;
}



}
}
