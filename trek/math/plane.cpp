#include "plane.hpp"

#include <stdexcept>

namespace trek {
namespace math {

using std::domain_error;

Plane::Plane(const Vec3& dot1, const Vec3& dot2, const Vec3& dot3) {
	norm = ((dot2 - dot1) & (dot3 - dot1)).ort();
	dist = -(norm * dot1);
}

Line3 Plane::getLine(const Plane& plane1, const Plane& plane2) {
	Line3 line;
	auto& p = line.point;
	auto& v = line.vector;
	const auto& n1 = plane1.norm;
	const auto& n2 = plane2.norm;

	v = Vec3(plane1.norm & plane2.norm).ort();
	/*Находим точку лежащую на прямой*/
	if(n1.x * n2.y - n1.x * n2.y != 0) {
		p.y = (n2.x * plane1.dist - n1.x * plane2.dist) / (n1.x * n2.y - n2.x * n1.y);
		if(n1.x != 0)
			p.x = (-plane1.dist - n1.y * p.y) / n1.x;
		else if(n2.x != 0)
			p.x = (-plane2.dist - n2.y * p.y) / n2.x;
		p.z = 0;
	} else if(n2.y * n1.z - n1.y * n2.z != 0) {
		p.z = (n1.y * plane2.dist - n2.y * plane1.dist) / (n2.y * n1.z - n1.y * n2.z);
		if(n1.y != 0)
			p.y = (-plane1.dist - n1.z * p.z) / n1.y;
		else if(n2.y != 0)
			p.y = (-plane2.dist - n2.z * p.z) / n2.y;
		p.x = 0;
	} else if(n2.x * n1.z - n1.x * n2.z != 0) {
		p.z = (n1.x * plane2.dist - n2.x * plane1.dist) / (n2.x * n1.z - n1.x * n2.z);
		if(n1.x != 0)
			p.x = (-plane1.dist - n1.z * p.z) / n1.x;
		else if(n2.x != 0)
			p.x = (-plane2.dist - n2.z * p.z) / n2.x;
		p.y = 0;
	} else
		throw domain_error("TLine3: can't find intersection of two planes");
	return line;
}

Vec3 Plane::cross(const Line3 &line) {
	auto p = norm * line.vector;
	if(p == 0)
		throw domain_error("Plane::cross plane and line are parallel");
	auto t = - ((norm * line.point) + dist) / p;
	return (line.vector * t) + line.point;
}

}
}
