#ifndef TREK_DATA_CTUDCRECORD_HPP
#define TREK_DATA_CTUDCRECORD_HPP

#include <chrono>
#include <vector>
#include <cstdint>
#include <memory>

#include "tdcrecord.hpp"
#include "structs.hpp"

namespace trek {
namespace data {

class CtudcRecord {
    using NevodPackagePtr = std::unique_ptr<NevodPackage>;
    using SystemClock  = std::chrono::high_resolution_clock;
    using TimePoint    = SystemClock::time_point;
    using Milliseconds = std::chrono::milliseconds;
public:
    class Type {
    public:
        Type();
        Type(bool hasTdc, bool hasNevod);
        bool hasTdcData() const;
        bool hasNevodPackage() const;
        void serialize(std::ostream& stream) const;
        void deserialize(std::istream& stream);
    private:
        uint8_t mType;
    };
public:
    CtudcRecord();
    CtudcRecord(std::istream& stream);
    CtudcRecord(uint64_t run, uint64_t number, const TimePoint& time);
    CtudcRecord(const CtudcRecord& other);
    void operator= (const CtudcRecord& other);

    void setTdcRecord(const TdcRecord& record);
    void setNevodPackage(const NevodPackage& package);

    void resetTdcRecord();
    void resetNevodPackage();

    void serialize(std::ostream& stream) const;
    void deserialize(std::istream& stream);

    const TdcRecord& tdcRecord() const;
    const NevodPackage& nevodPackage() const;

    bool hasTdcRecord() const;
    bool hasNevodPackage() const;

    uint64_t numberOfRecord() const;
    uint64_t numberOfRun() const;
    TimePoint time() const;

    void convertTdcWords(double koef);
protected:
    void serializeTime(std::ostream& stream, const TimePoint& time) const;
    void deserializeTime(std::istream& stream, TimePoint& time);
private:
    uint64_t  mNumberOfRun;
    uint64_t  mNumberOfRecord;
    Type      mType;
    TimePoint mTime;

    TdcRecord       mTdcRecord;
    NevodPackagePtr mNevodPackage;

};

} //data
} //trek

#endif // TREK_DATA_CTUDCRECORD_HPP
