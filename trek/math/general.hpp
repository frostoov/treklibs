#pragma once

namespace trek {
namespace math {

constexpr double PI    = 3.14159265358979323846;
constexpr double E     = 2.71828182845904523536;

/*!
 * \brief Перевод из радиан в градусы
 */
template<typename T>
inline T toDeg(const T& angle) {
    return angle * 180. / PI;
}

/*!
 * \brief Перевод из градусов в радианы
 */
template<typename T>
inline T toRad(const T& angle) {
    return angle * PI / 180.;
}

} //math
} //trek
