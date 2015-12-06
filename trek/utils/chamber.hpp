#pragma once

#include <trek/math/octahedron.hpp>
#include <trek/math/coordsystem.hpp>
#include <trek/data/eventrecord.hpp>

#include "trektypes.hpp"

namespace trek {

class Chamber {
public:
	Chamber(const ChamberDescription& chamberInfo);
	TrackDescription createTrack(const data::ChamHits& chamHits);
	math::Line2 lineProjection(math::Line3 line) const;

	uint32_t plane() const;
	uint32_t group() const;
	const ChamberPoints& points() const;
	const math::Octahedron& octahedron() const;
protected:
	static math::CoordSystem3 getChamberSystem(const ChamberPoints& pos);
	static math::Octahedron   getOctahedron(const ChamberPoints& pos);
private:
	ChamberDescription mDescription;
	math::CoordSystem3 mChamberSystem;
	math::Octahedron   mOctahedron;

	constexpr static double mChamberWidth   = 500;
	constexpr static double mChamberHeight  = 112;
	constexpr static double mChamberLength  = 4000;
};

}
