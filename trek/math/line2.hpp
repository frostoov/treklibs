#pragma once

#include "vec2.hpp"

namespace trek {
namespace math {
/*!
 * \class Line2
 * \author frostoov
 * \date 03/18/15
 * \file line2.hpp
 * \brief Прямая в двумерном пространстве
 */
struct Line2 {
    double k, b;

    /*!
     * \brief Создание прямой с коэфициетами k = 0, b = 0 (y = k*x + b)
     */
    Line2();
    /*!
     * \brief Создание прямой по коэфициентм (y = k*x + b)
     */
    Line2(double k, double b);
    /*!
     * \brief Создание прямой по двум точкам, через которые проходит прямая
     */
    Line2(const Vec2& dot1, const Vec2& dot2);
    /*!
     * \brief Создание прямой по точке, через которую проходит прямая, и направляющему вектору
     * prarm dot точка, через которую проходит прямая
     * param vec направляющий вектор прямой
     */
    static Line2 fromVectors(const Vec2& dot, const Vec2& vec);
    /*!
     * \brief Нахождение точки пересечения двух прямых
     * \param line1, line2 прямые в двухмерном пространстве
     */
    static Vec2 cross(const Line2& line1, const Line2& line2);
};


} //math
} //trek
