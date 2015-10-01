#include "vec2.hpp"

#include <cmath>
#include <stdexcept>
#include <ostream>

namespace trek {
namespace math {

using std::acos;
using std::pow;
using std::sqrt;
using std::out_of_range;
using std::runtime_error;

Vec2::Vec2(double x, double y)
    : mData{x, y} { }


bool operator==(const Vec2& a, const Vec2& b) {
    return a.x() == b.x() &&
           a.y() == b.y();
}

Vec2 operator+(const Vec2& a, const Vec2& b) {
    return {a.x() + b.x(),
            a.y() + b.y()};
}

Vec2 operator-(const Vec2& a, const Vec2& b) {
    return {a.x() - b.x(),
            a.y() - b.y()};
}

double operator*(const Vec2& a, const Vec2& b) {
    return a.x() * b.x() +
           a.y() * b.y();
}

Vec2 operator*(const Vec2& vec, double num) {
    return {vec.x()* num,
            vec.y()* num};
}

Vec2 operator*(double num, const Vec2& vec) {
    return {vec.x()* num,
            vec.y()* num};
}

Vec2 Vec2::operator +() const {
    return *this;
}

Vec2 Vec2::operator -() const {
    return { -mData[0],
             -mData[1]};
}

void Vec2::operator+=(const Vec2& vec) {
    mData[0] += vec.mData[0];
    mData[1] += vec.mData[1];
}

void Vec2::operator-=(const Vec2& vec) {
    mData[0] -= vec.mData[0];
    mData[1] -= vec.mData[1];
}

double Vec2::abs() const {
    return sqrt( pow(mData[0], 2) +
                 pow(mData[1], 2) );
}

double Vec2::operator[](size_t i) const {
    if(i < 2)
        return mData[i];
    else
        throw out_of_range("Vec2: out of range");
}

double& Vec2::operator[](size_t i) {
    if(i < 2)
        return mData[i];
    else
        throw out_of_range("Vec2: out of range");
}

Vec2 Vec2::ort() const {
    auto len = this->abs();
    if(len != 0)
        return {mData[0] / len, mData[1] / len};
    else
        return {0, 0};
}

double angle(const Vec2& a, const Vec2& b) {
    auto len = a.abs() * b.abs();
    if(len != 0)
        return acos((a * b) / len);
    else
        throw runtime_error("Vec2::angle: null vector");
}

void Vec2::rotate(double ang) {
    double s = sin(ang);
    double c = cos(ang);
    *this = {
        x()* c - y()* s,
        x()* s + y()* c,
    };
}

std::ostream& operator<<(std::ostream& stream, const Vec2& vec) {
    return stream << '(' << vec.x() << ", " << vec.y() << ')';
}

}
}
