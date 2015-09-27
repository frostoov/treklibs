#include "octahedron.hpp"

using std::array;

namespace trek {
namespace math {

Octahedron::Octahedron(const Vec3& vtx1, const Vec3& vtx2,
                       const Vec3& vtx3, const Vec3& vtx4,
                       const Vec3& vtx5, const Vec3& vtx6,
                       const Vec3& vtx7, const Vec3& vtx8)
    : mVertices{{vtx1, vtx2, vtx3, vtx4, vtx5, vtx6, vtx7, vtx8}} {}

std::vector<Vec3> Octahedron::checkIntersection(const Line3& line) const {
    Vec3 inPoint;
    std::vector<Vec3> retVec;
    for(const auto& plg : getPolygons()) {
        if(plg.checkIntersection(line, inPoint))
            retVec.push_back(inPoint);
    }

    return retVec;
}

Vec3& Octahedron::operator[](size_t i) {
    return mVertices.at(i);
}

std::array<Vec3, 8>& Octahedron::vertices() {
    return mVertices;
}

const std::array<Vec3, 8>& Octahedron::vertices() const {
    return mVertices;
}

const Vec3& Octahedron::operator[](size_t i) const {
    return mVertices.at(i);
}

array<Quadrangle3, 6> Octahedron::getPolygons() const {
    return {{
            Quadrangle3{mVertices[0], mVertices[1], mVertices[2], mVertices[3]},
            Quadrangle3{mVertices[4], mVertices[5], mVertices[6], mVertices[7]},
            Quadrangle3{mVertices[0], mVertices[1], mVertices[5], mVertices[4]},
            Quadrangle3{mVertices[3], mVertices[2], mVertices[6], mVertices[7]},
            Quadrangle3{mVertices[0], mVertices[4], mVertices[7], mVertices[3]},
            Quadrangle3{mVertices[1], mVertices[5], mVertices[6], mVertices[2]},
        }};
}


}
}
