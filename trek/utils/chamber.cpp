#include "chamber.hpp"
#include "chamberhandler.hpp"

namespace trek {

using math::Hexahedron;
using math::Line2;
using math::Line3;
using math::Vec2;
using math::Vec3;
using math::Plane;
using math::CoordSystem3;
using std::domain_error;

Chamber::Chamber(const ChamberDescription& chamberDescription)
	: mDescription(chamberDescription),
	  mChamberSystem(getChamberSystem(chamberDescription.points)),
	  mHexahedron(getHexahedron(chamberDescription.points)) {}

TrackDescription Chamber::createTrack(const data::ChamHits& eventTimes) {
	TrackDescription track;
	if(!createTrackDescription(eventTimes, mDescription, track))
		throw domain_error("Chamber::createTrack failed");
	return track;
}

CoordSystem3 Chamber::getChamberSystem(const ChamberPoints& pos) {
	auto xAxis = (pos[1] - pos[0]).ort();
	auto zAxis = (pos[2] - pos[0]).ort();
	auto yAxis = zAxis & xAxis;
	return {pos[0], xAxis, yAxis, zAxis};
}

Hexahedron Chamber::getHexahedron(const ChamberPoints& pos) {
	const int chamWidth = mChamberWidth / 2;

	/*Вспомогательные векторы*/
	const auto p13 = pos[2] - pos[0];
	const auto p12 = pos[1] - pos[0];
	const auto wVec = (p12 & p13).ort() * chamWidth;

	return {
		pos[0] + wVec,
		pos[0] - wVec,

		pos[1] - wVec,
		pos[1] + wVec,

		pos[2] + wVec,
		pos[2] - wVec,

		pos[2] - wVec + p12,
		pos[2] + wVec + p12,
	};
}

uint32_t Chamber::plane() const {
	return mDescription.plane;
}

uint32_t Chamber::group() const {
	return mDescription.group;
}

const ChamberPoints &Chamber::points() const {
	return mDescription.points;
}

const math::Hexahedron &Chamber::hexahedron() const {
	return mHexahedron;
}

Line2 Chamber::lineProjection(Line3 line) const {
	mChamberSystem.convertTo(line);
	return Line2::fromVectors(Vec2{line.point.x, line.point.y}, Vec2{line.vector.x, line.vector.y});
}

} //trek
