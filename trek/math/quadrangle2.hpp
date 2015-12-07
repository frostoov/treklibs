#pragma once

#include "vec2.hpp"
#include "line2.hpp"

#include <array>
#include <vector>

namespace trek {
namespace math {
/*!
 * \class Quadrangle2
 * \author frostoov
 * \date 03/18/15
 * \file quadrangle2.hpp
 * \brief Четырехугольник в двумерном пространстве
 */
class Quadrangle2 {
public:
	using Vertices = std::array<Vec2, 4>;
public:
	Quadrangle2(const Vec2& vtx1, const Vec2& vtx2, const Vec2& vtx3 , const Vec2& vtx4);
	Quadrangle2(Vec2&& vtx1, Vec2&& vtx2, Vec2&& vtx3, Vec2&& vtx4);
	Quadrangle2(const Vertices& vertices);
	Quadrangle2(Vertices&& vertices);

	/*!
	 * \brief Метод, определяет, лежит ли точка внутри четырехугольника
	 */
	bool hasPoint(const Vec2 &dot) const;

	/*!
	 * \brief Метод возвращает вершины четырехугольника
	 */
	const Vertices& vertices() const {
		return mVertices;
	}
private:
	Vertices mVertices;
};

}
}
