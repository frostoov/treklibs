#include "chamber.hpp"
#include "chamberhandler.hpp"

namespace trek {

using math::Octahedron;
using math::Line2;
using math::Line3;
using math::Vec2;
using math::Vec3;
using math::Plane;
using math::CoordSystem3;
using std::runtime_error;

Chamber::Chamber(const ChamberDescription& chamberDescription)
	: mDescription(chamberDescription),
	  mChamberSystem(getChamberSystem(chamberDescription.getPoints())),
	  mOctahedron(getOctahedron(chamberDescription.getPoints())),
	  mHasHit(false), mHasTrack(false) {}

bool Chamber::createTrack(const ChamberTimes& eventTimes) {
	try {
		mHasHit   = checkHit(eventTimes);
		// mTrack    = ChamberHandler::createTrackDescription(eventTimes, mDescription);
		// mHasTrack = true;
	} catch(...) {
		mHasTrack = false;
	}
	return mHasTrack;
}

void Chamber::resetData() {
	mHasHit   = false;
	mHasTrack = false;
}

CoordSystem3 Chamber::getChamberSystem(const ChamberPoints& pos) {
	auto xAxis = (pos[1] - pos[0]).ort();
	auto zAxis = (pos[2] - pos[0]).ort();
	auto yAxis = zAxis & xAxis;
	return {pos[0], xAxis, yAxis, zAxis};
}

const Line2& Chamber::getTrackLine() const {
	if(mHasTrack)
		return mTrack.line;
	else
		throw std::runtime_error("Chamber: getTrackLine: no track");
}

const TrackDescription& Chamber::getTrackDescription() const {
	if(mHasTrack)
		return mTrack;
	else
		throw std::runtime_error("Chamber: getTrackDescription: no track");
}

Plane Chamber::getTrackPlane() const {
	if(mHasTrack == false)
		throw runtime_error("Chamber: getTrackPlane: no track");
	return getTrackPlane(mTrack.line, mDescription.getPoints());
}

bool Chamber::hasHit() const {
	return mHasHit;
}

bool Chamber::hasTrack() const {
	return mHasTrack;
}

Line2 Chamber::getExternalProjection(const Line3& track) const {
	return getExternalProjection(track, mChamberSystem);
}

Line2 Chamber::getExternalProjection(Vec3 p1, Vec3 p2) const {
	return getExternalProjection(p1, p2, mChamberSystem);
}

Plane Chamber::getTrackPlane(const Line2& track, const ChamberPoints& pos) {
	/*Вспомогательные векторы*/
	const auto p13 = pos.at(2) - pos.at(0);
	const auto p12 = pos.at(1) - pos.at(0);
	const auto wVec = (p12 & p13).ort();

	auto pt1 = pos.at(0) + wVec * track.b();
	auto pt2 = pos.at(1) + wVec * (track.b() + track.k() * mChamberHeight);
	auto pt3 = pos.at(2) + wVec * track.b();

	return Plane(pt1, pt2, pt3);
}

Line2 Chamber::getExternalProjection(Line3 track, const CoordSystem3& system) {
	auto& dot1 = track.dot();
	auto  dot2 = track.dot() + track.vec() * 10;
	return getExternalProjection(dot1, dot2 , system);
}

Line2 Chamber::getExternalProjection(Vec3 p1, Vec3 p2, const CoordSystem3& system) {
	system.convertTo(p1);
	system.convertTo(p2);

	return {{p1.x(), p1.y() }, {p2.x(), p2.y() }};
}

bool Chamber::checkHit(const ChamberTimes& eventTimes) {
	for(const auto wireTimes : eventTimes) {
		if(!wireTimes.empty())
			return true;
	}
	return false;
}

Octahedron Chamber::getOctahedron(const ChamberPoints& pos) {
	const int chamWidth = mChamberWidth / 2;

	/*Вспомогательные векторы*/
	const auto p13 = pos.at(2) - pos.at(0);
	const auto p12 = pos.at(1) - pos.at(0);
	const auto wVec = (p12 & p13).ort() * chamWidth;

	return {
		pos.at(0) + wVec,
		pos.at(0) - wVec,

		pos.at(1) - wVec,
		pos.at(1) + wVec,

		pos.at(2) + wVec,
		pos.at(2) - wVec,

		pos.at(2) - wVec + p12,
		pos.at(2) + wVec + p12,
	};
}

} //trek
