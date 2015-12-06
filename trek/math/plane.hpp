#pragma once

#include "line3.hpp"

namespace trek {
namespace math {

struct Plane {
	Vec3 norm;
	double dist;
	Plane(const Vec3& dot1, const Vec3& dot2, const Vec3& dot3);
	static Line3 getLine(const Plane& plane1, const Plane& plane2);

	Vec3 cross(const Line3 &line);
};
}
}
