#include "chamberhandler.hpp"
#include "../data/eventrecord.hpp"

#include <limits>
#include <cmath>

namespace trek {

using std::abs;
using std::array;
using std::runtime_error;
using std::numeric_limits;

using math::Vec2;
using math::Line2;

using Indecies = std::array<unsigned, 4>;

static size_t getDepth(const ChamDistances & eventDistances);
static ChamDistances getDistances(const data::ChamHits& data, const ChamberDescription& chamDesc);
static TrackDescription createTrackDescription(const TrackDistances& distances);
static TrackDistances createTrackDistances(const ChamDistances & eventDistances, const Indecies& indices);
static TrackTimes createTrackTimes(const data::ChamHits& eventTimes, const Indecies& indices);
static double leastSquares(const Points& points, math::Line2& line);
static bool systemError(TrackDescription& track);
static double getSystemError(double r, double ang);

template <typename T> int sign(T val) {
	return (T(0) < val) - (val < T(0));
}

const std::array<math::Vec2, 4> mWires{{
		Vec2(41,  0.75),
		Vec2(51, -0.75),
		Vec2(61,  0.75),
		Vec2(71, -0.75),
	}};

bool createTrackDescription(
		const data::ChamHits& eventTimes,
        const ChamberDescription& chamDesc,
        TrackDescription& trackDesc) {
	ChamDistances eventDistances(getDistances(eventTimes, chamDesc));
	auto depth = getDepth(eventDistances);
	if(depth != 1)
		return false;

	trackDesc.deviation = numeric_limits<double>::infinity();

	Indecies ind;
	for(ind.at(0) = 0; ind.at(0) < eventDistances.at(0).size(); ++ind.at(0))
		for(ind.at(1) = 0; ind.at(1) < eventDistances.at(1).size(); ++ind.at(1))
			for(ind.at(2) = 0; ind.at(2) < eventDistances.at(2).size(); ++ind.at(2))
				for(ind.at(3) = 0; ind.at(3) < eventDistances.at(3).size(); ++ind.at(3)) {
					auto tempTrackDesc  = createTrackDescription(createTrackDistances(eventDistances, ind));
					if(tempTrackDesc.deviation != -1 && tempTrackDesc.deviation < trackDesc.deviation) {
						tempTrackDesc.times = createTrackTimes(eventTimes, ind);
						trackDesc = tempTrackDesc;
					}
				}
	if(trackDesc.deviation != numeric_limits<double>::infinity() && systemError(trackDesc))
		return true;
	else
		return false;
}

ChamDistances getDistances(const data::ChamHits& eventTimes, const ChamberDescription& chamDesc) {
	ChamDistances distances;
	for(size_t wire = 0; wire < eventTimes.size(); ++wire)
		for(auto msr :  eventTimes.at(wire)) {
			const auto& params = chamDesc.parameters.at(wire);
			if(msr > params.offset)
				distances.at(wire).push_back((msr - params.offset)*params.speed);
		}
	return distances;
}

size_t getDepth(const ChamDistances & eventDistances) {
	auto depth = numeric_limits<size_t>::max();
	for(const auto& wireData : eventDistances)
		if(wireData.size() < depth)
			depth = wireData.size();
	return depth;
}

bool systemError(TrackDescription& track) {
	double r;
	for(size_t i = 0; i < track.points.size(); ++i) {
		auto trackSign = sign(track.points[i].y);
		switch(trackSign * sign(mWires[i].y)) {
		case 1:
			r = (abs(track.points[i].y) > 6.2) ? 6.2 : track.points[i].y;
			break;
		case -1:
			r = (abs(track.points[i].y) > 3.6) ? 3.6 : track.points[i].y;
			break;
		default:
			return false;
		}
		track.points[i].y += trackSign * getSystemError(r, std::atan(track.line.k));
	}
	track.deviation = leastSquares(track.points, track.line);
	return true;
}

double getSystemError(double r, double ang) {
	return r * (1 / std::cos(ang) - 1);
}

TrackDistances createTrackDistances(const ChamDistances & eventDistances, const Indecies& indices) {
	TrackDistances trackDistances;
	for(size_t i = 0; i < trackDistances.size(); ++i)
		trackDistances.at(i) = eventDistances.at(i).at(indices.at(i) % eventDistances.at(i).size());
	return trackDistances;
}

TrackTimes createTrackTimes(const data::ChamHits& eventTimes, const Indecies& indices) {
	TrackTimes trackTimes;
	for(size_t i = 0; i < trackTimes.size(); ++i)
		trackTimes.at(i) = eventTimes.at(i).at(indices.at(i) % eventTimes.at(i).size());
	return trackTimes;
}

TrackDescription createTrackDescription(const TrackDistances& distances) {
	TrackDescription trackDesc;
	static Points tempPoints{mWires[0], mWires[1], mWires[2], mWires[3]};
	static Line2  tempLine;
	trackDesc.deviation = numeric_limits<double>::infinity();
	size_t numPermutations = std::pow(2, distances.size());

	for(size_t i = 0; i < numPermutations; ++i) {
		//Изменяем знаки на противоположные
		for(size_t j = 0; j < distances.size(); j++) {
			if(i & (1 << j))
				tempPoints[j].y = -static_cast<double>(distances[j]);
			else
				tempPoints[j].y =  static_cast<double>(distances[j]);
			tempPoints[j].y += mWires[j].y;
		}
		double tempDev = leastSquares(tempPoints, tempLine);
		if(tempDev != -1 && tempDev < trackDesc.deviation) {
			trackDesc.deviation = tempDev;
			trackDesc.line = tempLine;
			trackDesc.points = tempPoints;
		}
	}
	return trackDesc;
}

double leastSquares(const Points& points, Line2& line) {
	if(points.size() < 2)
		return -1;
	double sumX = 0, sumY = 0, sumXY = 0, sumXX = 0;
	for(const auto& p : points) {
		sumX  += p.x;
		sumY  += p.y;
		sumXY += p.x * p.y;
		sumXX += p.x * p.x;
	}
	auto exp = points.size() * sumXX - sumX * sumX;
	if(exp && std::abs(exp) > 1e-60) {
		line.k = (points.size() * sumXY - sumX * sumY) / exp;
		line.b = (sumY - line.k * sumX) / points.size();
		double dev = 0;
		for(const auto& p : points)
			dev += std::pow((line.k * p.x + line.b) - p.y, 2);
		return dev;
	} else
		return -1;
}

} //trek
