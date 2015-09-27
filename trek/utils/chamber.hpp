#pragma once

#include <trek/math/octahedron.hpp>
#include <trek/math/coordsystem.hpp>

#include "trektypes.hpp"

namespace trek {

class Chamber {
public:
    Chamber(const ChamberDescription& chamberInfo);
    bool createTrack(const ChamberTimes& eventTimes);
    void resetData();

    const math::Line2&   getTrackLine() const;
    const TrackDescription& getTrackDescription() const;

    math::Plane getTrackPlane() const;

    uint32_t getChamberPlane() const {
        return mDescription.getPlane();
    }
    uint32_t getChamberGroup() const {
        return mDescription.getGroup();
    }
    const ChamberPoints& getChamberPoints() const {
        return mDescription.getPoints();
    }
    const math::Octahedron& getOctahedron() const {
        return mOctahedron;
    }

    bool hasHit()   const;
    bool hasTrack() const;

    math::Line2 getExternalProjection(const math::Line3& track) const;
    math::Line2 getExternalProjection(math::Vec3 p1, math::Vec3 p2) const;
protected:
    static math::Plane getTrackPlane(const math::Line2& track, const ChamberPoints& pos);
    static math::Line2 getExternalProjection(math::Line3 track, const math::CoordSystem3& system);
    static math::Line2 getExternalProjection(math::Vec3 p1, math::Vec3 p2, const math::CoordSystem3& system);


    static bool checkHit(const ChamberTimes& eventTimes);
    static math::CoordSystem3 getChamberSystem(const ChamberPoints& pos);
    static math::Octahedron   getOctahedron(const ChamberPoints& pos);
private:
    ChamberDescription    mDescription;
    math::CoordSystem3 mChamberSystem;
    math::Octahedron   mOctahedron;
    TrackDescription      mTrack;

    bool mHasHit;
    bool mHasTrack;

    constexpr static double mChamberWidth   = 500;
    constexpr static double mChamberHeight  = 112;
    constexpr static double mChamberLength  = 4000;
};

}
