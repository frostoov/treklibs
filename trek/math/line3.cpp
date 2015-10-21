#include "line3.hpp"

namespace trek {
namespace math {

Line3::Line3(const Vec3& point, const Vec3& vector)
	: mPoint(point),
	  mVector(vector) { }

void Line3::rotateX(double ang) {
	mPoint.rotateX(ang);
	mVector.rotateX(ang);
}

void Line3::rotateY(double ang) {
	mPoint.rotateY(ang);
	mVector.rotateY(ang);
}

void Line3::rotateZ(double ang) {
	mPoint.rotateZ(ang);
	mVector.rotateZ(ang);
}

void Line3::rotate(const Vec3& vec, double ang) {
	mPoint.rotate(vec, ang);
	mVector.rotate(vec, ang);
}


Line3 Line3::fromPoints(const Vec3& point1, const Vec3& point2) {
	return Line3(point1, point2 - point1);
}

} //math
} //trek
