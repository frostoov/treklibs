#pragma once

#include "quadrangle3.hpp"

#include <vector>

namespace trek {
namespace math {


class Octahedron {
public:
	using Vertices = std::array<Vec3, 8>;
	using Polygons = std::array<Quadrangle3, 6>;
public:
	Octahedron(const Vec3& vtx1, const Vec3& vtx2, const Vec3& vtx3, const Vec3& vtx4,
	           const Vec3& vtx5, const Vec3& vtx6, const Vec3& vtx7, const Vec3& vtx8);
	Octahedron(Vec3&& vtx1, Vec3&& vtx2, Vec3&& vtx3, Vec3&& vtx4,
	           Vec3&& vtx5, Vec3&& vtx6, Vec3&& vtx7, Vec3&& vtx8);
	Octahedron(const Vertices& vertices);
	Octahedron(Vertices&& vertices);
	std::vector<Vec3> getIntersections(const Line3& line) const;
	bool checkIntersection(const Line3& line) const;

	const Vertices& vertices() const {
		return mVertices;
	}
	const Polygons& polygons() const {
		return mPolygons;
	}
protected:
	static Polygons getPolygons(const std::array<Vec3, 8>& vetices);
private:
	Vertices mVertices;
	Polygons mPolygons;
};

}
}
