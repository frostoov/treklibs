#pragma once

#include "vec3.hpp"

namespace trek {
namespace math {

struct Line3 {
	Vec3 point;
	Vec3 vector;

	Line3() = default;
	Line3(const Vec3& point_, const Vec3& vector_);

	static Line3 fromPoints(const Vec3& point1, const Vec3& point2);

	void rotateX(double ang);
	void rotateY(double ang);
	void rotateZ(double ang);
	void rotate(const Vec3& vec, double ang);
};

}
}
