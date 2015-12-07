#pragma once

#include "quadrangle3.hpp"

#include <vector>

namespace trek {
namespace math {
/*!
 * \class Hexahedron
 * \author frostoov
 * \date 03/18/15
 * \file hexahedron.hpp
 * \brief Шестигранник
 */
class Hexahedron {
public:
	using Vertices = std::array<Vec3, 8>;
	using Polygons = std::array<Quadrangle3, 6>;
public:
	Hexahedron(const Vec3& vtx1, const Vec3& vtx2, const Vec3& vtx3, const Vec3& vtx4,
	           const Vec3& vtx5, const Vec3& vtx6, const Vec3& vtx7, const Vec3& vtx8);
	Hexahedron(Vec3&& vtx1, Vec3&& vtx2, Vec3&& vtx3, Vec3&& vtx4,
	           Vec3&& vtx5, Vec3&& vtx6, Vec3&& vtx7, Vec3&& vtx8);
	Hexahedron(const Vertices& vertices);
	Hexahedron(Vertices&& vertices);
	/*!
	 * \brief Нахождение точек пересечения данного шестигранник и прямой
	 */
	std::vector<Vec3> cross(const Line3 &line) const;
	/*!
	 * \brief Метод, определяет пересекаются ли данноый шестигранник и прямая
	 */
	bool crossing(const Line3 &line) const;

	/*!
	 * \brief Вершины шестигранника
	 */
	const Vertices& vertices() const {
		return mVertices;
	}
	/*!
	 * \brief Четырехугольники шестигранника
	 */
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
