#include "ctudcrecord.hpp"

#include <trek/common/assertion.hpp>

namespace trek {
namespace data {

using std::runtime_error;
using std::chrono::duration_cast;
using std::make_unique;

template<typename Rep, typename Period>
static std::chrono::milliseconds toMilliseconds(const std::chrono::duration<Rep, Period>& duration) {
    return duration_cast<std::chrono::milliseconds>(duration);
}

CtudcRecord::CtudcRecord()
    : mNumberOfRun(0),
      mNumberOfRecord(0),
      mType(false, false),
      mTime(SystemClock::now()) { }

CtudcRecord::CtudcRecord(std::istream& stream) {
    trek::deserialize(stream, *this);
}

CtudcRecord::CtudcRecord(uint64_t run, uint64_t number, const CtudcRecord::TimePoint& time)
    : mNumberOfRun(run),
      mNumberOfRecord(number),
      mType(false, false),
      mTime(time)  { }

CtudcRecord::CtudcRecord(const CtudcRecord& other)
    : CtudcRecord(other.numberOfRun(),
                  other.numberOfRecord(),
                  other.time()) {
    other.hasTdcRecord() ? setTdcRecord(other.tdcRecord()) : resetTdcRecord();
    other.hasNevodPackage() ? setNevodPackage(other.nevodPackage()) : resetNevodPackage();
}

void CtudcRecord::operator= (const CtudcRecord& other) {
    mNumberOfRun    = other.numberOfRun();
    mNumberOfRecord = other.numberOfRecord();
    mTime = other.time();
    other.hasTdcRecord() ? setTdcRecord(other.tdcRecord()) : resetTdcRecord();
    other.hasNevodPackage() ? setNevodPackage(other.nevodPackage()) : resetNevodPackage();
}

void CtudcRecord::setTdcRecord(const TdcRecord& record) {
    mTdcRecord = record;
    mType = Type(true, mType.hasNevodPackage());
}

void CtudcRecord::setNevodPackage(const NevodPackage& package) {
    if(!mNevodPackage)
        mNevodPackage = make_unique<NevodPackage> (package);
    else
        *mNevodPackage = package;
    mType = Type(mType.hasTdcData(), true);
}

void CtudcRecord::resetTdcRecord() {
    mTdcRecord.clearTdcData();
    mType = Type(false, mType.hasNevodPackage());
}

void CtudcRecord::resetNevodPackage() {
    mNevodPackage.reset();
    mType = Type(mType.hasTdcData(), false);
}

void CtudcRecord::serialize(std::ostream& stream) const {
    trek::serialize(stream, mNumberOfRun);
    trek::serialize(stream, mNumberOfRecord);
    trek::serialize(stream, mType);
    serializeTime(stream, mTime);
    if(hasTdcRecord())
        trek::serialize(stream, mTdcRecord);
    if(hasNevodPackage())
        trek::serialize(stream, *mNevodPackage);
}

void CtudcRecord::deserialize(std::istream& stream) {
    trek::deserialize(stream, mNumberOfRun);
    trek::deserialize(stream, mNumberOfRecord);
    trek::deserialize(stream, mType);
    deserializeTime(stream, mTime);
    if(mType.hasTdcData())
        trek::deserialize(stream, mTdcRecord);
    else
        resetTdcRecord();
    if(mType.hasNevodPackage()) {
        if(!mNevodPackage)
            mNevodPackage = make_unique<NevodPackage>();
        trek::deserialize(stream, *mNevodPackage);
    } else
        resetNevodPackage();
}

const NevodPackage& CtudcRecord::nevodPackage() const {
    if(mType.hasNevodPackage())
        return *mNevodPackage;
    else
        throw Assertion("CtudcRecord::getNevodPacakge: no nevod data");
}

const TdcRecord& CtudcRecord::tdcRecord() const {
    if(mType.hasTdcData())
        return mTdcRecord;
    else
        throw Assertion("CtudcRecord::getTdcData: no tdc data");
}

bool CtudcRecord::hasTdcRecord() const {
    return mType.hasTdcData();
}

bool CtudcRecord::hasNevodPackage() const {
    return mType.hasNevodPackage();
}

uint64_t CtudcRecord::numberOfRecord() const {
    return mNumberOfRecord;
}

uint64_t CtudcRecord::numberOfRun() const {
    return mNumberOfRun;
}

CtudcRecord::TimePoint CtudcRecord::time() const {
    return mTime;
}

void CtudcRecord::convertTdcWords(double koef) {
    mTdcRecord.convertTdcWords(koef);
}

void CtudcRecord::serializeTime(std::ostream& stream, const CtudcRecord::TimePoint& time) const {
    int64_t timeInMilliseconds = toMilliseconds(time.time_since_epoch()).count();
    trek::serialize(stream, timeInMilliseconds);
}

void CtudcRecord::deserializeTime(std::istream& stream, CtudcRecord::TimePoint& time) {
    int64_t timeInMilliseconds;
    trek::deserialize(stream, timeInMilliseconds);
    time = TimePoint(std::chrono::duration_cast<TimePoint::duration> (Milliseconds(timeInMilliseconds)));
}

CtudcRecord::Type::Type() : mType(0) { }

CtudcRecord::Type::Type(bool hasTdc, bool hasNevod)
    : mType(0) {
    mType |= (hasTdc   & 1) << 0;
    mType |= (hasNevod & 1) << 1;
}

bool CtudcRecord::Type::hasTdcData() const {
    return bool((mType >> 0) & 1);
}

bool CtudcRecord::Type::hasNevodPackage() const {
    return bool((mType >> 1) & 1);
}

void CtudcRecord::Type::serialize(std::ostream& stream) const {
    trek::serialize(stream, mType);
}

void CtudcRecord::Type::deserialize(std::istream& stream) {
    trek::deserialize(stream, mType);
}

} //data
} //trek
