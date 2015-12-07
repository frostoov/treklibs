#pragma once

#include "vec3.hpp"

namespace trek {
namespace math {
/*!
 * \class Line3
 * \author frostoov
 * \date 03/18/15
 * \file line3.hpp
 * \brief Прямая в трехмерном пространстве
 */
struct Line3 {
	Vec3 point;
	Vec3 vector;

	Line3() = default;
	/*!
	 * \brief Создание прямой по точке, через которую проходит прямая, и направляющему вектору
	 * prarm point точка, через которую проходит прямая
	 * param vector направляющий вектор прямой
	 */
	Line3(const Vec3& point, const Vec3& vector);
	/*!
	 * \brief Создание прямой по двум точкам, через которые проходит прямая
	 */
	static Line3 fromPoints(const Vec3& point1, const Vec3& point2);
	/*!
	 * \brief Вращение прямой вокруг оси X
	 * \param ang Угол, на которое производится вращение
	 */
	void rotateX(double ang);
	/*!
	 * \brief Вращение прямой вокруг оси Y
	 * \param ang Угол, на которое производится вращение
	 */
	void rotateY(double ang);
	/*!
	 * \brief Вращение прямой вокруг оси Z
	 * \param ang Угол, на которое производится вращение
	 */
	void rotateZ(double ang);
	/*!
	 * \brief Вращение прямой вокруг заданого вектора
	 * \param vec Вектор, вокруг которого, производится вращение
	 * \param ang Угол, на которое производится вращение
	 */
	void rotate(const Vec3& vec, double ang);
};

}
}
