#include "quadrangle3.hpp"

#include "quadrangle2.hpp"
#include "coordsystem.hpp"

namespace trek {
namespace math {

using std::move;

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

bool Quadrangle3::checkPoint(Vec3 point) const {
    mCoordSystem.convertTo(point);
    return mQuadrangle2.checkPoint({point.x(), point.y()});
}

bool Quadrangle3::getIntersection(const Line3& line, Vec3& point) const {
    if(getPlane().getIntersectionPoint(line, point) ) {
        return checkPoint(point);
    } else {
        return false;
    }
}

bool Quadrangle3::checkIntersection(const Line3& line) const {
    Vec3 point;
    if(getPlane().getIntersectionPoint(line, point) ) {
        return checkPoint(point);
    } else {
        return false;
    }
}

Plane Quadrangle3::getPlane() const {
    return {mVertices[0], mVertices[1], mVertices[2]};
}

Quadrangle2 Quadrangle3::getQuadrangle2(const Vertices& vertices, const CoordSystem3& coorSystem) {
    auto v = vertices;

    Quadrangle2::Vertices vertices2;
    for(size_t i = 0; i < v.size(); ++i) {
        mCoordSystem.convertTo(v[i]);
        vertices2[i] = {v[i].x(), v[i].y()};
    }
    return vertices2;
}

CoordSystem3 Quadrangle3::getCoordinateSystem(const std::array<Vec3, 4>& vertices) const {
    auto newX = (vertices.at(1) - vertices.at(0)).ort();
    auto newY = (vertices.at(3) - vertices.at(0)).ort();
    auto newZ = (newX & newY).ort();
    return {mVertices.at(0), newX, newZ};
}

}
}
