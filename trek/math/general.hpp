#pragma once

namespace trek {
namespace math {

constexpr double PI    = 3.14159265358979323846;
constexpr double E     = 2.71828182845904523536;

template<typename T>
T toDeg(const T& angle) {
	return angle * 180. / PI;
}

template<typename T>
T toRad(const T& angle) {
	return angle * PI / 180.;
}

} //math
} //trek
