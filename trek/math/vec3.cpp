#include "vec3.hpp"

#include <cmath>
#include <stdexcept>
#include <istream>

namespace trek {
namespace math {

using std::sqrt;
using std::pow;
using std::acos;
using std::runtime_error;
using std::out_of_range;

Vec3::Vec3(double x, double y, double z)
    : mData{x, y, z} { }

Vec3::Vec3(const double* data)
    : mData{data[0], data[1], data[2]} {}

void Vec3::operator+=(const Vec3& vec) {
    mData[0] += vec.mData[0];
    mData[1] += vec.mData[1];
    mData[2] += vec.mData[2];
}

void Vec3::operator-=(const Vec3& vec) {
    mData[0] -= vec.mData[0];
    mData[1] -= vec.mData[1];
    mData[2] -= vec.mData[2];
}

Vec3 Vec3::ort() const {
    auto len = abs();
    if(len) {
        len = 1 / len;
        return {mData[0]* len, mData[1]* len, mData[2]* len};
    } else
        return {0, 0, 0};
}

double Vec3::abs() const {
    return sqrt(pow(mData[0], 2) +
                pow(mData[1], 2) +
                pow(mData[2], 2));
}

double& Vec3::x() {
    return mData[0];
}

double& Vec3::y() {
    return mData[1];
}

double& Vec3::z() {
    return mData[2];
}

double Vec3::x() const {
    return mData[0];
}

double Vec3::y() const {
    return mData[1];
}

double Vec3::z() const {
    return mData[2];
}

double* Vec3::data() {
    return mData;
}

const double* Vec3::data() const {
    return mData;
}

double Vec3::operator[](unsigned int i) const {
    if(i < 3)
        return mData[i];
    else
        throw out_of_range("Vec3::operator[]: out of range");
}

void Vec3::rotateX(double ang) {
    auto c = std::cos(ang), s = std::sin(ang);
    auto Y = y(), Z = z();
    mData[1] = Y * c - Z * s;
    mData[2] = Y * s + Z * c;
}

void Vec3::rotateY(double ang) {
    auto c = std::cos(ang), s = std::sin(ang);
    auto X = x(), Z = z();
    mData[0] = X * c + Z * s;
    mData[2] = Z * c - X * s;
}

void Vec3::rotateZ(double ang) {
    auto c = std::cos(ang), s = std::sin(ang);
    auto X = x(), Y = y();
    mData[0] = X * c - Y * s;
    mData[1] = X * s + Y * c;
}

void Vec3::rotate(const Vec3& vec, double ang) {
    auto v = vec.ort();
    auto c = std::cos(ang);
    auto s = std::sin(ang);
    auto d = 1 - c;
    double V1[] = {c + d * v.x()* v.x(),       d * v.x()* v.y() - s * v.z(), d * v.x()* v.z() + s * v.y() };
    double V2[] = {d * v.x()* v.y() + s * v.z(), c + d * v.y()* v.y(),	     d * v.y()* v.z() + s * v.x() };
    double V3[] = {d * v.x()* v.z() + s * v.y(), c * v.y()* v.z() + s * v.x(), c + d * v.z()* v.z()     };
    *this = {
        V1[0]* x() + V1[1]* y() + V1[2]* z(),
        V2[0]* x() + V2[1]* y() + V2[2]* z(),
        V3[0]* x() + V3[1]* y() + V3[2]* z(),
    };
}

double* Vec3::begin() {
    return mData;
}

double* Vec3::end() {
    return mData + 3;
}

const double* Vec3::begin() const {
    return mData;
}

const double* Vec3::end() const {
    return mData + 3;
}

double& Vec3::operator[](unsigned int i) {
    if(i < 3)
        return mData[i];
    else
        throw out_of_range("Vec3::operator[]: out of range");
}

Vec3 Vec3::operator-() const {
    return { -mData[0], -mData[1], -mData[2]};
}

Vec3 Vec3::operator+() const {
    return *this;
}

double operator*(const Vec3& a, const Vec3& b) {
    return  a.x() * b.x() +
            a.y() * b.y() +
            a.z() * b.z();
}

Vec3 operator&(const Vec3& a, const Vec3& b) {
    return {
        a[1]* b[2] - a[2]* b[1],
        a[2]* b[0] - a[0]* b[2],
        a[0]* b[1] - a[1]* b[0],
    };
}

Vec3 operator*(const Vec3& vec, double num) {
    return { vec[0]* num,
             vec[1]* num,
             vec[2]* num };
}

Vec3 operator/(const Vec3& vec, double num) {
    return { vec[0] / num,
             vec[1] / num,
             vec[2] / num };
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return {a[0] + b[0],
            a[1] + b[1],
            a[2] + b[2]};
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return {a[0] - b[0],
            a[1] - b[1],
            a[2] - b[2]};
}

double range(const Vec3& a, const Vec3& b) {
    return (a - b).abs();
}

double angle(const Vec3& a, const Vec3& b) {
    auto len = a.abs() * b.abs();
    if(len != 0) {
        return acos( (a * b) / len );
    } else {
        throw std::runtime_error("Vec3::angle: null vector");
    }
}

bool operator==(const Vec3& a, const Vec3& b) {
    return a[0] == b[0] &&
           a[1] == b[1] &&
            a[2] == b[2];
}

std::ostream&operator<<(std::ostream& stream, const Vec3& vec) {
    return stream << '{' << vec.x() << ", " << vec.y() << ", " << vec.z() << '}';
}

}
}
