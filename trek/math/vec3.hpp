#pragma once

#include <iosfwd>

namespace trek {
namespace math {

struct Vec3 {
	double x, y, z;
	Vec3(double x_ = 0, double y_ = 0, double z_ = 0);

	Vec3 operator+() const;
	Vec3 operator-() const;
	void operator+= (const Vec3& vec);
	void operator-= (const Vec3& vec);
	Vec3 ort() const;
	double abs() const;

	void rotateX(double ang);
	void rotateY(double ang);
	void rotateZ(double ang);
	void rotate(const Vec3& vec, double ang);
};

bool operator==(const Vec3& a, const Vec3& b);
double operator* (const Vec3& a, const Vec3& b);
Vec3 operator& (const Vec3& a, const Vec3& b);

Vec3 operator* (const Vec3& vec, double num);
Vec3 operator/ (const Vec3& vec, double num);

Vec3 operator+ (const Vec3& a, const Vec3& b);
Vec3 operator- (const Vec3& a, const Vec3& b);

double range(const Vec3& a, const Vec3& b);

double angle(const Vec3& a, const Vec3& b);

std::ostream& operator<<(std::ostream& stream, const Vec3& vec);

} //math
} //trek
