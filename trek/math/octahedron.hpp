#pragma once

#include "quadrangle3.hpp"

#include <vector>

namespace trek {
namespace math {


class Octahedron {
public:
    Octahedron() = default;
    Octahedron(const Vec3& vtx1, const Vec3& vtx2, const Vec3& vtx3, const Vec3& vtx4,
               const Vec3& vtx5, const Vec3& vtx6, const Vec3& vtx7, const Vec3& vtx8);
    std::vector<Vec3> checkIntersection(const Line3& line) const;
    Vec3& operator[](size_t i);
    const Vec3& operator[](size_t i) const;

    std::array<Quadrangle3, 6> getPolygons() const;

    std::array<Vec3, 8>& vertices();
    const std::array<Vec3, 8>& vertices() const;
private:
    std::array<Vec3, 8> mVertices;
};

}
}
