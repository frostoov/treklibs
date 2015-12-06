#include "line3.hpp"

namespace trek {
namespace math {

Line3::Line3(const Vec3& point_, const Vec3& vector_)
	: point(point_),
	  vector(vector_) { }

void Line3::rotateX(double ang) {
	point.rotateX(ang);
	vector.rotateX(ang);
}

void Line3::rotateY(double ang) {
	point.rotateY(ang);
	vector.rotateY(ang);
}

void Line3::rotateZ(double ang) {
	point.rotateZ(ang);
	vector.rotateZ(ang);
}

void Line3::rotate(const Vec3& vec, double ang) {
	point.rotate(vec, ang);
	vector.rotate(vec, ang);
}


Line3 Line3::fromPoints(const Vec3& point1, const Vec3& point2) {
	return Line3(point1, point2 - point1);
}

} //math
} //trek
