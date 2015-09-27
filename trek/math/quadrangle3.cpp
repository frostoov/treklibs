#include "quadrangle3.hpp"

#include "quadrangle2.hpp"
#include "coordsystem.hpp"

#include <vector>

namespace trek {
namespace math {

Quadrangle3::Quadrangle3(const Vec3& vtx1, const Vec3& vtx2, const Vec3& vtx3, const Vec3& vtx4)
    : mVertices{{vtx1, vtx2, vtx3, vtx4}} {}

Vec3& Quadrangle3::operator[](std::size_t i) {
    return mVertices.at(i);
}

const Vec3& Quadrangle3::operator[](std::size_t i) const {
    return mVertices.at(i);
}

bool Quadrangle3::checkPoint(Vec3 point) const {
    auto newX = (mVertices.at(1) - mVertices.at(0)).ort();
    auto newY = (mVertices.at(3) - mVertices.at(0)).ort();
    auto newZ = (newX & newY).ort();
    CoordSystem3 coordSystem(mVertices.at(0), newX, newZ);
    auto vertices = mVertices;

    std::vector<Vec2> vertices2;
    for(auto& v : vertices) {
        coordSystem.convertTo(v);
        vertices2.push_back({v.x(), v.y()});
    }

    Quadrangle2 q(vertices2[0], vertices2[1], vertices2[2], vertices2[3]);
    coordSystem.convertTo(point);
    return q.checkPoint({point.x(), point.y()});
}

bool Quadrangle3::checkIntersection(const Line3& line, Vec3& point) const {
    point = getPlane().getIntersectionPoint(line);
    return checkPoint(point);
}

Plane Quadrangle3::getPlane() const {
    return {mVertices[0], mVertices[1], mVertices[2]};
}

}
}
