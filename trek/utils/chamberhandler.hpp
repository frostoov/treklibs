#pragma once

#include <cstdint>
#include <array>

#include <trek/math/line2.hpp>
#include <trek/math/coordsystem.hpp>
#include <trek/data/eventrecord.hpp>

#include "trektypes.hpp"

namespace trek {

class Chamber;


/**
 * @class ChamberHandler
 * @author frostoov
 * @date 03/15/15
 * @file chambermanager.hpp
 * @brief Обработка mChamberTrackданны события дрейфовой камеры
 */
class ChamberHandler {
	using Indecies = std::array<unsigned, 4>;
public:
	static bool createTrackDescription(const data::ChamHits& eventTimes,
	                                   const ChamberDescription& chamDesc,
	                                   TrackDescription& trackDesc);
protected:
	static size_t getDepth(const ChamDistances & eventDistances);
	static ChamDistances getDistances(const data::ChamHits& data, const ChamberDescription& chamDesc);
	static TrackDescription createTrackDescription(const TrackDistances& distances);
	static TrackDistances createTrackDistances(const ChamDistances & eventDistances, const Indecies& indices);
	static TrackTimes createTrackTimes(const data::ChamHits& eventTimes, const Indecies& indices);
	static double leastSquares(const Points& points, math::Line2& line);
	static bool systemError(TrackDescription& track);
	static double getSystemError(double r, double ang);
private:
	static const std::array<math::Vec2, 4> mWires;
};

} //trek
