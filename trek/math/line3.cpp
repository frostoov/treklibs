#include "line3.hpp"

namespace trek {
namespace math {

Line3::Line3(const Vec3& dot1, const Vec3& dot2) {
    if(dot1.abs() < dot2.abs()) {
        mVec = (dot2 - dot1).ort();
        mDot = dot1;
    } else {
        mVec = (dot1 - dot2).ort();
        mDot = dot2;
    }
}

Vec3& Line3::dot() {
    return mDot;
}

Vec3& Line3::vec() {
    return mVec;
}

const Vec3& Line3::dot() const {
    return mDot;
}

const Vec3& Line3::vec() const {
    return mVec;
}

void Line3::rotateX(double ang) {
    mDot.rotateX(ang);
    mVec.rotateX(ang);
}

void Line3::rotateY(double ang) {
    mDot.rotateY(ang);
    mVec.rotateY(ang);
}

void Line3::rotateZ(double ang) {
    mDot.rotateZ(ang);
    mVec.rotateZ(ang);
}

void Line3::rotate(const Vec3& vec, double ang) {
    mDot.rotate(vec, ang);
    mVec.rotate(vec, ang);
}


}
}
