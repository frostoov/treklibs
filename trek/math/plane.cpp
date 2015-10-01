#include "plane.hpp"

#include <stdexcept>

namespace trek {
namespace math {

using std::runtime_error;

Plane::Plane(const Vec3& dot1, const Vec3& dot2, const Vec3& dot3) {
    mNorm = ((dot2 - dot1) & (dot3 - dot1)).ort();
    mD = - (mNorm * dot1);
}

Line3 Plane::getLine(const Plane& plane1, const Plane& plane2) {
    Line3 line;
    auto& dot = line.dot();
    auto& vec = line.vec();
    const auto& norm1 = plane1.norm();
    const auto& norm2 = plane2.norm();

    vec = Vec3(plane1.norm() & plane2.norm()).ort();
    /*Находим точку лежащую на прямой*/
    if(norm1.x() * norm2.y() - norm1.x() * norm2.y() != 0) {
        dot.y() = (norm2.x() * plane1.d() - norm1.x() * plane2.d()) /
                  (norm1.x() * norm2.y()  - norm2.x() * norm1.y());
        if(norm1.x() != 0)
            dot.x() = (-plane1.d() - norm1.y() * dot.y()) / norm1.x();
        else if(norm2.x() != 0)
            dot.x() = (-plane2.d() - norm2.y() * dot.y()) / norm2.x();
        dot.z() = 0;
    } else if(norm2.y() * norm1.z() - norm1.y() * norm2.z() != 0) {
        dot.z() = (norm1.y() * plane2.d() - norm2.y() * plane1.d()) /
                  (norm2.y() * norm1.z()  - norm1.y() * norm2.z());
        if(norm1.y() != 0)
            dot.y() = (-plane1.d() - norm1.z() * dot.z()) / norm1.y();
        else if(norm2.y() != 0)
            dot.y() = (-plane2.d() - norm2.z() * dot.z()) / norm2.y();
        dot.x() = 0;
    } else if(norm2.x() * norm1.z() - norm1.x() * norm2.z() != 0) {
        dot.z() = (norm1.x() * plane2.d() - norm2.x() * plane1.d()) /
                  (norm2.x() * norm1.z()  - norm1.x() * norm2.z());
        if(norm1.x() != 0)
            dot.x() = (-plane1.d() - norm1.z() * dot.z()) / norm1.x();
        else if(norm2.x() != 0)
            dot.x() = (-plane2.d() - norm2.z() * dot.z()) / norm2.x();
        dot.y() = 0;
    } else
        throw runtime_error("TLine3: can't find intersection of two planes");
    return line;
}

bool Plane::getIntersectionPoint(const Line3& line, Vec3& point) {
    auto p = (mNorm * line.vec());
    if(p == 0)
        return false;
    auto t = - ((mNorm * line.dot()) + mD) / p;
    point = (line.vec() * t) + line.dot();
    return true;
}

}
}
