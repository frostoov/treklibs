#include "coordsystem.hpp"

#include <cmath>
#include <stdexcept>

namespace trek {
namespace math {

using std::cos;

CoordSystem3::CoordSystem3(const Vec3& offset, const Vec3& X, const Vec3& Y, const Vec3& Z)
	: mOffset(offset),
	  V1{X}, V2{Y}, V3{Z} { }

void CoordSystem3::convertTo(Vec3& vec) const {
	shift(vec);
	rotate(vec);
}

void CoordSystem3::convertTo(Line3& line) const {
	rotate(line.vector);
	convertTo(line.point);
}

void CoordSystem3::shift(Vec3& vec) const {
	vec -= mOffset;
}

void CoordSystem3::rotate(Vec3& vec) const {
	vec = {
		vec * V1,
		vec * V2,
		vec * V3,
	};
}

}
}
