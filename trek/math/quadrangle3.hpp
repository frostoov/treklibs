#pragma once

#include "line3.hpp"
#include "plane.hpp"

#include <array>

namespace trek {
namespace math {


class Quadrangle3 {
public:
    Quadrangle3(const Vec3& vtx1, const Vec3& vtx2, const Vec3& vtx3 , const Vec3& vtx4);
    const Vec3& operator[](size_t i) const;
    Vec3& operator[](size_t i);
    bool checkPoint(Vec3 vec) const;

    bool checkIntersection(const Line3& line, Vec3& point) const;

    Plane getPlane() const;
private:
    std::array<Vec3, 4> mVertices;
};

}
}
