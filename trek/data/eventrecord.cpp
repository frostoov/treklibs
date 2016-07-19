#include "eventrecord.hpp"

#include <trek/common/serialization.hpp>

namespace trek {
namespace data {

using std::istream;
using std::ostream;
using std::unordered_set;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::duration;

static auto toMillis = [](const auto& dur) {
    return duration_cast<milliseconds>(dur);
};

EventRecord::EventRecord()
    : mNRun(0),
      mNEvent(0),
      mTimePoint(SystemClock::now()) { }

EventRecord::EventRecord(uint64_t nRun, uint64_t nEvent, const EventHits& hits)
    : mNRun(nRun),
      mNEvent(nEvent),
      mTimePoint(SystemClock::now()),
      mHits(hits) { }

EventRecord::EventRecord(istream& stream) {
    trek::deserialize(stream, *this);
}

const HitRecord& EventRecord::operator[](size_t i) const {
    return mHits.at(i);
}

uint64_t EventRecord::nRun() const {
    return mNRun;
}

uint64_t EventRecord::nEvent() const {
    return mNEvent;
}

EventRecord::TimePoint EventRecord::time() const {
    return mTimePoint;
}

TrekHits EventRecord::getTrekHits() const {
    TrekHits trekEvent;
    for(const auto& hit : mHits) {
        if(trekEvent.count(hit.chamber()) == 0)
            trekEvent.insert({hit.chamber(), ChamHits() });
        trekEvent.at(hit.chamber()).at(hit.wire()).push_back(hit.time());
    }
    return trekEvent;
}

ChamHits EventRecord::getChamberHits(unsigned cham) const {
    ChamHits chamEvent;
    for(const auto& hit : mHits) {
        if(hit.chamber() == cham)
            chamEvent.at(hit.wire()).push_back(hit.time());
    }
    return chamEvent;
}

unordered_set<unsigned> EventRecord::getTriggeredChambers() const {
    unordered_set<unsigned> triggChambers;
    for(const auto& hit : mHits)
        triggChambers.insert(hit.chamber());
    return triggChambers;
}

void EventRecord::serialize(ostream& stream) const {
    trek::serialize(stream, mNRun);
    trek::serialize(stream, mNEvent);
    serializeTime(stream, mTimePoint);
    trek::serialize(stream, uint32_t(mHits.size()));
    for(const auto& hit : mHits)
        trek::serialize(stream, hit);
}

void EventRecord::deserialize(istream& stream) {
    trek::deserialize(stream, mNRun);
    trek::deserialize(stream, mNEvent);
    deserializeTime(stream, mTimePoint);
    uint32_t size;
    trek::deserialize(stream, size);
    mHits.resize(size, {HitRecord::Type::leading, 0, 0, 0});
    for(auto& hit : mHits)
        trek::deserialize(stream, hit);
}

void EventRecord::serializeTime(ostream& stream, const TimePoint& time) const {
    int64_t timeInMillis = toMillis(time.time_since_epoch()).count();
    trek::serialize(stream, timeInMillis);
}

void EventRecord::deserializeTime(istream& stream, TimePoint& time) {
    int64_t millis;
    trek::deserialize(stream, millis);
    time = TimePoint(duration_cast<TimePoint::duration> (milliseconds(millis)));
}


} //data
} //trek
