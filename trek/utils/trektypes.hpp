#pragma once

#include <trek/math/vec2.hpp>
#include <trek/math/line2.hpp>
#include <trek/math/vec3.hpp>

#include <array>
#include <vector>
#include <unordered_map>

namespace trek {

using DoubleVector     = std::vector<double>;
using WordVector	   = std::vector<uint32_t>;
using ChamberTimes     = std::array<WordVector, 4>;
using ChamberDistances = std::array<DoubleVector, 4>;
using TrackDistances   = std::array<double, 4>;
using TrackTimes       = std::array<uint32_t, 4>;

using Points            = std::vector<math::Vec2>;
using ChamberPoints     = std::array<math::Vec3, 3>;

class WireParameters {
public:
	WireParameters(uint32_t offset = 0, double speed = 0) : mOffset(offset), mSpeed(speed) {}
	void setOffset(uint32_t offset) {
		mOffset = offset;
	}
	void setSpeed(double speed)     {
		mSpeed = speed;
	}
	uint32_t getOffset() const {
		return mOffset;
	}
	double   getSpeed()  const {
		return mSpeed;
	}
private:
	uint32_t mOffset;
	double   mSpeed;
};

using ChamberParameters = std::array<WireParameters, 4>;

/**
 * @class ChamberDescription
 * @author frostoov
 * @date 03/18/15
 * @file chamber.hpp
 * @brief Описание дрейфовой камеры
 */
class ChamberDescription {
public:
	ChamberDescription(const ChamberPoints& points,
	                   const ChamberParameters& parameters,
	                   uint32_t plane, uint32_t group) :
		mPoints(points),
		mParameters(parameters),
		mPlane(plane),
		mGroup(group) {}
	const ChamberPoints& getPoints() const {
		return mPoints;
	}
	const ChamberParameters& getParameters() const {
		return mParameters;
	}
	uint32_t getPlane() const {
		return mPlane;
	}
	uint32_t getGroup() const {
		return mGroup;
	}
	void setParameters(const ChamberParameters& parameters) {
		mParameters = parameters;
	}
private:
	ChamberPoints     mPoints;     /**< Точки дрейфовой камеры */
	ChamberParameters mParameters; /**< Параметры для каждой проволки*/
	uint32_t          mPlane;      /**< Номер плоскости дрейфовой камеры */
	uint32_t          mGroup;      /**< Номер группы дрейфовой камеры */
};

/**
 * @class TrackDescription
 * @author frostoov
 * @date 03/15/15
 * @file chamber.hpp
 * @brief Структура с данными одного трека
 */
struct TrackDescription {
	math::Line2 line;		/**< Прямая трека */
	Points         points;		/**< Точки, по которым был восстановлен трек */
	double         deviation;   /**< Отклонение прямой */
	TrackTimes	   times;		/**< Вермена с TDC */
};

using ChamberConfig = std::unordered_map<uintmax_t, ChamberDescription>;


} //trek
