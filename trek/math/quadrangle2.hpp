#pragma once

#include "vec2.hpp"
#include <array>

namespace trek {
namespace math {

class Quadrangle2 {
public:
    Quadrangle2(const Vec2& vtx1, const Vec2& vtx2, const Vec2& vtx3 , const Vec2& vtx4);
    bool checkPoint(const Vec2& dot) const;
    const std::array<Vec2, 4>& Vertices() const;
private:
    std::array<Vec2, 4> mVertices;
};

}
}
