#include "octahedron.hpp"

using std::array;

namespace trek {
namespace math {

using std::move;

Octahedron::Octahedron(const Vec3& vtx1, const Vec3& vtx2,
                       const Vec3& vtx3, const Vec3& vtx4,
                       const Vec3& vtx5, const Vec3& vtx6,
                       const Vec3& vtx7, const Vec3& vtx8)
	: mVertices{{vtx1, vtx2, vtx3, vtx4, vtx5, vtx6, vtx7, vtx8}},
	  mPolygons(getPolygons(mVertices)) { }

Octahedron::Octahedron(Vec3&& vtx1, Vec3&& vtx2, Vec3&& vtx3, Vec3&& vtx4,
                       Vec3&& vtx5, Vec3&& vtx6, Vec3&& vtx7, Vec3&& vtx8)
	: mVertices{{move(vtx1), move(vtx2), move(vtx3), move(vtx4), move(vtx5), move(vtx6), move(vtx7), move(vtx8)}},
	  mPolygons(getPolygons(mVertices)) { }

Octahedron::Octahedron(const Vertices& vertices)
	: mVertices(vertices),
	  mPolygons(getPolygons(mVertices)) { }

Octahedron::Octahedron(Vertices&& vertices)
	: mVertices( move(vertices) ),
	  mPolygons(getPolygons(mVertices)) { }

std::vector<Vec3> Octahedron::getIntersections(const Line3& line) const {
	Vec3 inPoint;
	std::vector<Vec3> retVec;
	for(const auto& plg : polygons()) {
		if(plg.getIntersection(line, inPoint))
			retVec.push_back(inPoint);
	}

	return retVec;
}

bool Octahedron::checkIntersection(const Line3& line) const {
	for(const auto& plg : polygons())
		if(plg.checkIntersection(line))
			return true;

	return false;
}

std::array<Quadrangle3, 6> Octahedron::getPolygons(const std::array<Vec3, 8>& vertices) {
	return {{
		Quadrangle3{vertices[0], vertices[1], vertices[2], vertices[3]},
		Quadrangle3{vertices[4], vertices[5], vertices[6], vertices[7]},
		Quadrangle3{vertices[0], vertices[1], vertices[5], vertices[4]},
		Quadrangle3{vertices[3], vertices[2], vertices[6], vertices[7]},
		Quadrangle3{vertices[0], vertices[4], vertices[7], vertices[3]},
		Quadrangle3{vertices[1], vertices[5], vertices[6], vertices[2]},
	}};
}


}
}
