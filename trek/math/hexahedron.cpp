#include "hexahedron.hpp"

using std::array;

namespace trek {
namespace math {

using std::move;
using std::vector;

Hexahedron::Hexahedron(const Vec3& vtx1, const Vec3& vtx2,
                       const Vec3& vtx3, const Vec3& vtx4,
                       const Vec3& vtx5, const Vec3& vtx6,
                       const Vec3& vtx7, const Vec3& vtx8)
	: mVertices{{vtx1, vtx2, vtx3, vtx4, vtx5, vtx6, vtx7, vtx8}},
      mPolygons(getPolygons(mVertices)) { }

Hexahedron::Hexahedron(Vec3&& vtx1, Vec3&& vtx2, Vec3&& vtx3, Vec3&& vtx4,
                       Vec3&& vtx5, Vec3&& vtx6, Vec3&& vtx7, Vec3&& vtx8)
	: mVertices{{move(vtx1), move(vtx2), move(vtx3), move(vtx4), move(vtx5), move(vtx6), move(vtx7), move(vtx8)}},
      mPolygons(getPolygons(mVertices)) { }

Hexahedron::Hexahedron(const Vertices& vertices)
	: mVertices(vertices),
      mPolygons(getPolygons(mVertices)) { }

Hexahedron::Hexahedron(Vertices&& vertices)
	: mVertices( move(vertices) ),
	  mPolygons(getPolygons(mVertices)) { }

vector<Vec3> Hexahedron::cross(const Line3 &line) const {
	std::vector<Vec3> retVec;
	for(const auto& plg : mPolygons) {
		try {
			retVec.push_back(plg.cross(line));
		} catch(std::domain_error& e) {
			//nothing
		}
	}
	return retVec;
}

bool Hexahedron::crossing(const Line3 &line) const {
	for(const auto& plg : mPolygons)
		if(plg.crossing(line))
			return true;

	return false;
}

std::array<Quadrangle3, 6> Hexahedron::getPolygons(const std::array<Vec3, 8>& vertices) {
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
