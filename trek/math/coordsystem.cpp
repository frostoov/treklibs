#include "coordsystem.hpp"

#include <cmath>

namespace trek {
namespace math {

using std::cos;
using std::sin;


CoordSystem3::CoordSystem3(const Vec3& offset, const Vec3& X, const Vec3& Z)
    : mOffset(offset) {
    static const Vec3 x = Vec3(1, 0, 0);
    static const Vec3 z = Vec3(0, 0, 1);
    //Line of nodes
    auto n = (z & Z).ort();
    if(n == Vec3(0, 0, 0))
        n = x;

    //Euler angles
    auto mAlpha = angle(X, n), mGama = angle(x, n), mBeta = angle(z, Z);

    auto sinA = sin(mAlpha), sinB = sin(mBeta), sinY = sin(mGama);
    auto cosA = cos(mAlpha), cosB = cos(mBeta), cosY = cos(mGama);

    V1[0] = cosA * cosY - sinA * cosB * sinY, V1[1] = -cosA * sinY - sinA * cosB * cosY, V1[2] = sinA * sinB;
    V2[0] = sinA * cosY + cosA * cosB * sinY, V2[1] = -sinA * sinY + cosA * cosB * cosY, V2[2] = -cosA * sinB;
    V3[0] = sinB * sinY,                      V3[1] = sinB * cosY,                       V3[2] = cosB;
}

void CoordSystem3::convertTo(Vec3& vec) const {
    shift(vec);
    rotate(vec);
}

void CoordSystem3::convertTo(Line3& line) const {
    rotate(line.vec());
    convertTo(line.dot());
}

void CoordSystem3::shift(Vec3& vec) const {
    vec -= mOffset;
}

void CoordSystem3::rotate(Vec3& vec) const {
    vec = {
        vec.x()* V1[0] + vec.y()* V1[1] + vec.z()* V1[2],
        vec.x()* V2[0] + vec.y()* V2[1] + vec.z()* V2[2],
        vec.x()* V3[0] + vec.y()* V3[1] + vec.z()* V3[2],
    };
}

}
}
