#pragma once
#include "line2.hpp"
#include "line3.hpp"

namespace trek {
namespace math {
/*!
* \class CoordSystem3
* \author frostoov
* \date 03/18/15
* \file coordsystem.hpp
* \brief Система координат в трехмерном пространстве
*/
class CoordSystem3 {
public:
	/*!
	 * \brief Создание системы координат по точке начала системы координат и ортам осей координат (относительно старой системы коодинат)
	 * \param offset Точка начала новой системы координат в старой системе координат
	 * \param X Ось X новой системы координат в старой системе координат
	 * \param Y Ось Y новой системы координат в старой системе координат
	 * \param Z Ось Z новой системы координат в старой системе координат
	 */
	CoordSystem3(const Vec3& offset, const Vec3& X, const Vec3& Y, const Vec3& Z);
	/*!
	 * \brief Преобразование вектора из старой систмы координат в данную
	 */
	void convertTo(Vec3& vec) const;
	/*!
	 * \brief Преобразование прямой из старой систмы координат в данную
	 */
	void convertTo(Line3& line) const;
protected:
	void rotate(Vec3& vec) const;
	void shift(Vec3& vec) const;
private:
	Vec3 mOffset;
	Vec3 V1;
	Vec3 V2;
	Vec3 V3;
};

} //math
} //trek
