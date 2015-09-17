#ifndef TREKHANDLER_HPP
#define TREKHANDLER_HPP

#include <trek/data/tdcrecord.hpp>
#include "chamber.hpp"

namespace trek {

class TrekHandler {
    using Octahedron = vecmath::Octahedron;
    using Vec3       = vecmath::Vec3;
    using Line2      = vecmath::Line2;
    using Line3      = vecmath::Line3;
    using TdcRecord	 = trek::data::TdcRecord;
    using ChamberMap = std::unordered_map<uintmax_t, Chamber>;
public:
    TrekHandler(const ChamberConfig& config);
    const ChamberMap& getChambers() const {
        return mChambers;
    }

    void loadEvent(const trek::data::TdcRecord& rawEvent);
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

#endif // TREKHANDLER_HPP
