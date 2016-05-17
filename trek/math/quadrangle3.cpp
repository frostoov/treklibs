#include "quadrangle3.hpp"

#include "quadrangle2.hpp"
#include "coordsystem.hpp"

namespace trek {
namespace math {

using std::move;
using std::domain_error;

Quadrangle3::Quadrangle3(const Vec3& vtx1, const Vec3& vtx2, const Vec3& vtx3, const Vec3& vtx4)
    : mVertices{{vtx1, vtx2, vtx3, vtx4}},
mCoordSystem(getCoordinateSystem(mVertices)),
mQuadrangle2(getQuadrangle2(mVertices, mCoordSystem)) { }

Quadrangle3::Quadrangle3(Vec3&& vtx1, Vec3&& vtx2, Vec3&& vtx3, Vec3&& vtx4)
    : mVertices{{move(vtx1), move(vtx2), move(vtx3), move(vtx4) }},
mCoordSystem(getCoordinateSystem(mVertices)),
mQuadrangle2(getQuadrangle2(mVertices, mCoordSystem)) { }

Quadrangle3::Quadrangle3(const Quadrangle3::Vertices& vertices)
    : mVertices(vertices),
      mCoordSystem(getCoordinateSystem(mVertices)),
      mQuadrangle2(getQuadrangle2(mVertices, mCoordSystem)) { }

Quadrangle3::Quadrangle3(Quadrangle3::Vertices&& vertices)
    : mVertices(move(vertices)),
      mCoordSystem(getCoordinateSystem(mVertices)),
      mQuadrangle2(getQuadrangle2(mVertices, mCoordSystem)) { }

bool Quadrangle3::hasPoint(Vec3 point) const {
    mCoordSystem.convertTo(point);
    return mQuadrangle2.hasPoint({point.x, point.y});
}

Vec3 Quadrangle3::cross(const Line3& line) const {
    auto c = plane().cross(line);
    if(!hasPoint(c))
        throw domain_error("Quadrangle3::cross no cross");
    return c;
}

bool Quadrangle3::crossing(const Line3& line) const {
    try {
        auto c = plane().cross(line);
        return hasPoint(c);
    } catch(std::domain_error&) {
        return false;
    }
}

Plane Quadrangle3::plane() const {
    return {mVertices[0], mVertices[1], mVertices[2]};
}

Quadrangle2 Quadrangle3::getQuadrangle2(Vertices v, const CoordSystem3& coorSystem) {
    Quadrangle2::Vertices vertices2;
    for(size_t i = 0; i < v.size(); ++i) {
        mCoordSystem.convertTo(v[i]);
        vertices2[i] = {v[i].x, v[i].y};
    }
    return vertices2;
}

CoordSystem3 Quadrangle3::getCoordinateSystem(const Vertices& vertices) const {
    auto newX = (vertices[1] - vertices[0]).ort();
    auto newY = (vertices[3] - vertices[0]).ort();
    auto newZ = (newX & newY).ort();
    return {vertices[0], newX, newY, newZ};
}

}
}
