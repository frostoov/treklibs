#ifndef CHAMBER_HPP
#define CHAMBER_HPP

#include <vecmath/figures.hpp>
#include <vecmath/coordsystem.hpp>

#include "trektypes.hpp"

namespace trek {

class Chamber {
public:
    Chamber(const ChamberDescription& chamberInfo);
    bool createTrack(const ChamberTimes& eventTimes);
    void resetData();

    const vecmath::Line2&   getTrackLine() const;
    const TrackDescription& getTrackDescription() const;

    vecmath::Plane getTrackPlane() const;

    uint32_t getChamberPlane() const {
        return mDescription.getPlane();
    }
    uint32_t getChamberGroup() const {
        return mDescription.getGroup();
    }
    const ChamberPoints& getChamberPoints() const {
        return mDescription.getPoints();
    }
    const vecmath::Octahedron& getOctahedron() const {
        return mOctahedron;
    }

    bool hasHit()   const;
    bool hasTrack() const;

    vecmath::Line2 getExternalProjection(const vecmath::Line3& track) const;
    vecmath::Line2 getExternalProjection(vecmath::Vec3 p1, vecmath::Vec3 p2) const;
protected:
    static vecmath::Plane getTrackPlane(const vecmath::Line2& track, const ChamberPoints& pos);
    static vecmath::Line2 getExternalProjection(vecmath::Line3 track, const vecmath::CoordSystem3& system);
    static vecmath::Line2 getExternalProjection(vecmath::Vec3 p1, vecmath::Vec3 p2, const vecmath::CoordSystem3& system);


    static bool checkHit(const ChamberTimes& eventTimes);
    static vecmath::CoordSystem3 getChamberSystem(const ChamberPoints& pos);
    static vecmath::Octahedron   getOctahedron(const ChamberPoints& pos);
private:
    ChamberDescription    mDescription;
    vecmath::CoordSystem3 mChamberSystem;
    vecmath::Octahedron   mOctahedron;
    TrackDescription      mTrack;

    bool mHasHit;
    bool mHasTrack;

    constexpr static double mChamberWidth   = 500;
    constexpr static double mChamberHeight  = 112;
    constexpr static double mChamberLength  = 4000;
};

}

#endif // CHAMBER_HPP
