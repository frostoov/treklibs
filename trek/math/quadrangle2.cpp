#include "quadrangle2.hpp"

#include <cmath>

namespace trek {
namespace math {

using std::abs;

Quadrangle2::Quadrangle2(const Vec2& vtx1, const Vec2& vtx2, const Vec2& vtx3, const Vec2& vtx4)
    : mVertices{{vtx1, vtx2, vtx3, vtx4}} { }

bool Quadrangle2::checkPoint(const Vec2& point) const {
    Vec2 cen((mVertices[0] + mVertices[1] + mVertices[2] + mVertices[3]) * 0.25);
    for(short k = 0, l = 1 ; k < 4; ++k, ++l) {
        if(l == 4) l = 0;
        auto norm = Vec2(
            mVertices[l].y() - mVertices[k].y(),
            mVertices[k].x() - mVertices[l].x()
        ).ort();
        auto C = norm * mVertices[k];
        auto distDot = norm * point - C;
        auto distCen = norm * cen - C;
        if(abs(distCen) < 2) {
            if(abs(distDot) > 2)
                return false;
        } else if(distDot * distCen < 0)
            return false;
    }
    return true;
}

const std::array<Vec2, 4>& Quadrangle2::Vertices() const {
    return mVertices;
}

}
}
