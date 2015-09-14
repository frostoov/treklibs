#include "tdcrecord.hpp"

#include <trek/common/serialization.hpp>

namespace trek {
namespace data {

using std::istream;
using std::unordered_set;

TdcRecord::TdcRecord(std::istream& stream) {
    trek::deserialize(stream, *this);
}

TdcRecord::TdcRecord(const WordVector& eventWords)
    : mTdcWords(eventWords) { }

uint32_t TdcRecord::getMesurement(uint32_t word) {
    return (word & 0x7ffff);
}

uint32_t TdcRecord::getChamber(uint32_t word) {
    return ((word >> 24) & 31);
}

uint32_t TdcRecord::getWire(uint32_t word) {
    return ((word >> 19) & 3);
}

const WordVector& TdcRecord::getData() const {
    return mTdcWords;
}

TdcRecord::TrekEvent TdcRecord::getTrekEvent() const {
    TrekEvent trekEvent;
    for(auto word : mTdcWords) {
        auto cham = getChamber(word);
        auto wire = getWire(word);
        auto msr  = getMesurement(word);
        if(trekEvent.count(cham) == 0)
            trekEvent.insert({cham, EventTimes() });
        trekEvent.at(cham).at(wire).push_back(msr);
    }
    return trekEvent;
}

TdcRecord::EventTimes TdcRecord::getChamberEvent(size_t cham) const {
    EventTimes chamEvent;
    for(auto word : mTdcWords) {
        if(getChamber(word) == cham)
            chamEvent.at(getWire(word)).push_back(getMesurement(word));
    }
    return chamEvent;
}

unordered_set<uintmax_t> TdcRecord::getTriggeredChambers() const {
    unordered_set<uintmax_t> triggChambers;
    for(auto word : mTdcWords)
        triggChambers.insert(getChamber(word));
    return triggChambers;
}

void TdcRecord::setTdcData(const WordVector& data) {
    mTdcWords = data;
}

void TdcRecord::convertTdcWords(double koef) {
    for(auto& word : mTdcWords) {
        uint32_t temp = getMesurement(word) * koef;
        temp &= 0x7FFFF;
        word &= 0xFFF80000;
        word |= temp;
    }
}

void TdcRecord::clearTdcData() {
    mTdcWords.clear();
}

void TdcRecord::serialize(std::ostream& stream) const {
    trek::serialize(stream, static_cast<uint32_t>(mTdcWords.size()));
    trek::serialize(stream, mTdcWords);
}

void TdcRecord::deserialize(std::istream& stream) {
    uint32_t size;
    trek::deserialize(stream, size);
    mTdcWords.resize(size);
    trek::deserialize(stream, mTdcWords);
}

} //data
} //trek
