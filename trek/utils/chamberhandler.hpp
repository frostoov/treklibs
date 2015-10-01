#pragma once

#include <cstdint>
#include <array>

#include <trek/math/line2.hpp>
#include <trek/math/coordsystem.hpp>

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
    using Indecies = std::array<uintmax_t, 4>;
public:
    static bool createTrackDescription(const ChamberTimes& eventTimes,
                                       const ChamberDescription& chamDesc,
                                       TrackDescription& trackDesc);
protected:
    static size_t           getDepth(const ChamberDistances& eventDistances);
    static ChamberDistances getDistances(const ChamberTimes& data, const ChamberDescription& chamDesc);
    static TrackDescription createTrackDescription(const TrackDistances& distances);
    static TrackDistances   createTrackDistances(const ChamberDistances& eventDistances, const Indecies& indices);
    static TrackTimes       createTrackTimes(const ChamberTimes& eventTimes, const Indecies& indices);
    static double	leastSquares(const Points& points, math::Line2& line);
    static bool	    systemError(TrackDescription& track);
    static double	getSystemError(double r, double ang);
private:
    static const std::array<math::Vec2, 4> mWires;
};

} //trek
