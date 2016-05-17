#pragma once

#include "line3.hpp"

namespace trek {
namespace math {

/*!
 * \class Plane
 * \author frostoov
 * \date 03/18/15
 * \file plane.hpp
 * \brief Плокость
 */
struct Plane {
    Vec3 norm;
    double dist;
    /*!
     * \brief Создание плоскости по трем точка
     */
    Plane(const Vec3& dot1, const Vec3& dot2, const Vec3& dot3);
    /*!
     * \brief Нахождение пересечения двух плоскостей
     */
    static Line3 getLine(const Plane& plane1, const Plane& plane2);

    /*!
     * \brief Нахождение данной плоскости и прямой
     */
    Vec3 cross(const Line3& line);
};
}
}
