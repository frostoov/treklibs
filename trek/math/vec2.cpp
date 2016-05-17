#include "vec2.hpp"

#include <cmath>
#include <stdexcept>
#include <ostream>

namespace trek {
namespace math {

using std::acos;
using std::pow;
using std::sqrt;
using std::domain_error;

Vec2::Vec2(double x_, double y_)
    : x(x_), y(y_) { }

bool operator==(const Vec2& a, const Vec2& b) {
    return a.x == b.x && a.y == b.y;
}

Vec2 operator+(const Vec2& a, const Vec2& b) {
    return {a.x + b.x, a.y + b.y};
}

Vec2 operator-(const Vec2& a, const Vec2& b) {
    return {a.x - b.x, a.y - b.y};
}

double operator*(const Vec2& a, const Vec2& b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 operator*(const Vec2& vec, double num) {
    return {vec.x * num, vec.y * num};
}

Vec2 operator*(double num, const Vec2& vec) {
    return {vec.x * num, vec.y * num};
}

Vec2 Vec2::operator +() const {
    return *this;
}

Vec2 Vec2::operator -() const {
    return { -x, -y};
}

void Vec2::operator+=(const Vec2& vec) {
    x += vec.x;
    y += vec.y;
}

void Vec2::operator-=(const Vec2& vec) {
    x -= vec.x;
    y -= vec.y;
}

double Vec2::abs() const {
    return sqrt( pow(x, 2) + pow(y, 2) );
}

Vec2 Vec2::ort() const {
    auto len = this->abs();
    if(len != 0)
        return {x / len, y / len};
    else
        return {0, 0};
}

double angle(const Vec2& a, const Vec2& b) {
    auto len = a.abs() * b.abs();
    if(len == 0)
        throw domain_error("Vec2::angle: null vector");
    return acos((a * b) / len);
}

void Vec2::rotate(double ang) {
    double s = sin(ang);
    double c = cos(ang);
    *this = {
        x* c - y * s,
        x* s + y * c,
    };
}

std::ostream& operator<<(std::ostream& stream, const Vec2& vec) {
    return stream << '(' << vec.x << ", " << vec.y << ')';
}

}
}
