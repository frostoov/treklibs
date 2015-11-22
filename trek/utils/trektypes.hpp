#pragma once

#include <trek/math/vec2.hpp>
#include <trek/math/line2.hpp>
#include <trek/math/vec3.hpp>

#include <array>
#include <vector>
#include <unordered_map>

namespace trek {

using ChamDistances   = std::array<std::vector<double>, 4>;
using TrackDistances  = std::array<double, 4>;
using TrackTimes      = std::array<unsigned, 4>;

using Points            = std::vector<math::Vec2>;
using ChamberPoints     = std::array<math::Vec3, 3>;

struct WireParameters {
	WireParameters(unsigned offset_ = 0, double speed_ = 0)
			: offset(offset_),
			  speed(speed_) {}
	unsigned offset;
	double   speed;
};

using ChamberParameters = std::array<WireParameters, 4>;

/**
 * @class ChamberDescription
 * @author frostoov
 * @date 03/18/15
 * @file chamber.hpp
 * @brief Описание дрейфовой камеры
 */
struct ChamberDescription {
	ChamberDescription(
			const ChamberPoints& points_,
			const ChamberParameters& parameters_,
			uint32_t plane_,
			uint32_t group_)
			: points(points_),
			  parameters(parameters_),
			  plane(plane_),
			  group(group_) {}
	ChamberPoints     points;     /**< Точки дрейфовой камеры */
	ChamberParameters parameters; /**< Параметры для каждой проволки*/
	uint32_t          plane;      /**< Номер плоскости дрейфовой камеры */
	uint32_t          group;      /**< Номер группы дрейфовой камеры */
};

/**
 * @class TrackDescription
 * @author frostoov
 * @date 03/15/15
 * @file chamber.hpp
 * @brief Структура с данными одного трека
 */
struct TrackDescription {
	math::Line2    line;		/**< Прямая трека */
	Points         points;		/**< Точки, по которым был восстановлен трек */
	double         deviation;   /**< Отклонение прямой */
	TrackTimes	   times;		/**< Вермена с TDC */
};

using ChamberConfig = std::unordered_map<uintmax_t, ChamberDescription>;


} //trek
