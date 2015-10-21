#pragma once

#include "line3.hpp"
#include "plane.hpp"
#include "coordsystem.hpp"
#include "quadrangle2.hpp"

#include <array>

namespace trek {
namespace math {


class Quadrangle3 {
public:
	using Vertices = std::array<Vec3, 4>;
public:
	Quadrangle3(const Vec3& vtx1, const Vec3& vtx2, const Vec3& vtx3 , const Vec3& vtx4);
	Quadrangle3(Vec3&& vtx1, Vec3&& vtx2, Vec3&& vtx3 , Vec3&& vtx4);
	Quadrangle3(const Vertices& vertices);
	Quadrangle3(Vertices&& vertices);
	bool checkPoint(Vec3 vec) const;
	bool getIntersection(const Line3& line, Vec3& point) const;
	bool checkIntersection(const Line3& line) const;

	Plane getPlane() const;
protected:
	CoordSystem3 getCoordinateSystem(const Vertices& vertices) const;
	Quadrangle2 getQuadrangle2(Vertices v, const CoordSystem3 &coorSystem);
private:
	Vertices     mVertices;
	CoordSystem3 mCoordSystem;
	Quadrangle2  mQuadrangle2;
};

}
}
