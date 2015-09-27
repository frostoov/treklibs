#pragma once

#include "vec3.hpp"

namespace trek {
namespace math {

class Line3 {
public:
    Line3() {}
    Line3(const Vec3& dot1, const Vec3& dot2);

    Vec3& dot();
    Vec3& vec();

    const Vec3& dot() const;
    const Vec3& vec() const;
    void rotateX(double ang);
    void rotateY(double ang);
    void rotateZ(double ang);
    void rotate(const Vec3& vec, double ang);
private:
    Vec3 mDot;
    Vec3 mVec;
};

}
}
