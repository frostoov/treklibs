#pragma once

#include "line3.hpp"

namespace trek {
namespace math {

class Plane {
public:
	Plane(const Vec3& dot1, const Vec3& dot2, const Vec3& dot3);

	static Line3 getLine(const Plane& plane1, const Plane& plane2);

	Vec3& norm() {
		return mNorm;
	}
	double& d() {
		return mD;
	}

	const Vec3&	norm() const {
		return mNorm;
	}
	double d() const {
		return mD;
	}

	bool getIntersectionPoint(const Line3& line, Vec3& point);
private:
	Vec3 mNorm;
	double mD;
};
}
}
