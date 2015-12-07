#include "vec3.hpp"

#include <cmath>
#include <stdexcept>
#include <istream>

namespace trek {
namespace math {

using std::sqrt;
using std::pow;
using std::acos;
using std::domain_error;

Vec3::Vec3(double x_, double y_, double z_)
	: x(x_), y(y_), z(z_) { }


void Vec3::operator+=(const Vec3& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

void Vec3::operator-=(const Vec3& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

Vec3 Vec3::ort() const {
	auto len = abs();
	if(len != 0)
		return {x / len, y / len, z / len};
	else
		return {0, 0, 0};
}

double Vec3::abs() const {
	return sqrt(pow(x, 2) +  pow(y, 2) + pow(z, 2));
}

void Vec3::rotateX(double ang) {
	auto c = std::cos(ang), s = std::sin(ang);
	auto Y = y, Z = z;
	y = Y * c - Z * s;
	z = Y * s + Z * c;
}

void Vec3::rotateY(double ang) {
	auto c = std::cos(ang), s = std::sin(ang);
	auto X = x, Z = z;
	x = X * c + Z * s;
	z = Z * c - X * s;
}

void Vec3::rotateZ(double ang) {
	auto c = std::cos(ang), s = std::sin(ang);
	auto X = x, Y = y;
	x = X * c - Y * s;
	y = X * s + Y * c;
}

void Vec3::rotate(const Vec3& vec, double ang) {
	auto v = vec.ort();
	auto c = std::cos(ang);
	auto s = std::sin(ang);
	auto d = 1 - c;
	double V1[] = {c + d * v.x* v.x,       d * v.x* v.y - s * v.z, d * v.x* v.z + s * v.y };
	double V2[] = {d * v.x* v.y + s * v.z, c + d * v.y* v.y,	     d * v.y* v.z + s * v.x };
	double V3[] = {d * v.x* v.z + s * v.y, c * v.y* v.z + s * v.x, c + d * v.z* v.z     };
	*this = {
		V1[0]* x + V1[1]* y + V1[2]* z,
		V2[0]* x + V2[1]* y + V2[2]* z,
		V3[0]* x + V3[1]* y + V3[2]* z,
	};
}

Vec3 Vec3::operator-() const {
	return { -x, -y, -z};
}

Vec3 Vec3::operator+() const {
	return *this;
}

double operator*(const Vec3& a, const Vec3& b) {
	return  a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec3 operator&(const Vec3& a, const Vec3& b) {
	return {
		a.y* b.z - a.z* b.y,
		a.z* b.x - a.x* b.z,
		a.x* b.y - a.y* b.x,
	};
}

Vec3 operator*(const Vec3& vec, double num) {
	return {vec.x*num, vec.y*num, vec.z*num};
}

Vec3 operator/(const Vec3& vec, double num) {
	return {vec.x/num, vec.y/num, vec.z/num};
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
	return {a.x - b.x, a.y - b.y, a.z - b.z};
}

double angle(const Vec3& a, const Vec3& b) {
	auto len = a.abs() * b.abs();
	if(len == 0)
		throw domain_error("Vec3::angle: null vector");
	return acos( (a * b) / len );
}

bool operator==(const Vec3& a, const Vec3& b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

std::ostream& operator<<(std::ostream& stream, const Vec3& vec) {
	return stream << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
}

}
}
