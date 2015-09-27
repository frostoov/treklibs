#pragma once
#include "line2.hpp"
#include "line3.hpp"

namespace trek {
namespace math {


class CoordSystem3 {
public:
    CoordSystem3(const Vec3& offset, const Vec3& X, const Vec3& Z);
    void convertTo(Vec3& vec) const;
    void convertTo(Line3& line) const;

private:
    Vec3 mOffset;
    double V1[3];
    double V2[3];
    double V3[3];
};

} //math
} //trek
