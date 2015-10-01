#pragma once

#include "vec3.hpp"

namespace trek {
namespace math {

class Line3 {
public:
    Line3() = default;
    Line3(const Vec3& point, const Vec3& vector);

    static Line3 fromPoints(const Vec3& point1, const Vec3& point2);

    Vec3& dot() {
        return mPoint;
    }
    Vec3& vec() {
        return mVector;
    }

    const Vec3& dot() const {
        return mPoint;
    }
    const Vec3& vec() const {
        return mVector;
    }

    void rotateX(double ang);
    void rotateY(double ang);
    void rotateZ(double ang);
    void rotate(const Vec3& vec, double ang);
private:
    Vec3 mPoint;
    Vec3 mVector;
};

}
}
