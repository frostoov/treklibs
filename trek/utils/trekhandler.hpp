#pragma once

#include "chamber.hpp"

#include <trek/data/eventrecord.hpp>

namespace trek {

class TrekHandler {
	using Octahedron = math::Octahedron;
	using Vec3       = math::Vec3;
	using Line2      = math::Line2;
	using Line3      = math::Line3;
	using TdcRecord	 = trek::data::EventRecord;
	using ChamberMap = std::unordered_map<uintmax_t, Chamber>;
public:
	TrekHandler(const ChamberConfig& config);
	const ChamberMap& getChambers() const {
		return mChambers;
	}

	void loadEvent(const trek::data::EventRecord & rawEvent);
	void loadChambers(const ChamberConfig& chams);
	bool createTrack();

	bool hasTrack() const {
		return mHasTrack;
	}
	const Line3& getTTrack() const {
		return mTTrack;
	}
protected:
	static Line3 createTrack(const Chamber& cham1, const Chamber& cham2);
private:
	ChamberMap mChambers;
	Line3      mTTrack;
	bool  mHasTrack;
};

}
