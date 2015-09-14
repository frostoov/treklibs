#include "tdcsettings.hpp"

namespace trek {
namespace data {

Settings::Settings()
    : mEdgeDetection(EdgeDetection::leading),
      mLsb(Lsb::ps100) { }

bool Settings::operator == (const Settings& other) {
    if(this == &other)
        return true;
    return getTriggerMode() == other.getTriggerMode() &&
           getAlmostFull()  == other.getAlmostFull() &&
           getControl()     == other.getControl() &&
           getDeadTime()    == other.getDeadTime() &&
           getEdgeDetection() == other.getEdgeDetection() &&
           getEventBLT() == other.getEventBLT() &&
           getLsb() == other.getLsb() &&
           getStatus() == other.getStatus() &&
           getTdcMeta() == other.getTdcMeta() &&
           getTriggerSubtraction() == other.getTriggerSubtraction() &&
           getWindowOffset() == other.getWindowOffset() &&
           getWindowWidth() == other.getWindowWidth();
}

bool Settings::operator != (const Settings& other) {
    return !(*this == other);
}

void Settings::serialize(std::ostream& stream) const {
    trek::serialize(stream, mTriggerMode);
    trek::serialize(stream, mTriggerSubtraction);
    trek::serialize(stream, mTdcMeta);
    trek::serialize(stream, mWindowWidth);
    trek::serialize(stream, mWindowOffset);
    trek::serialize(stream, mEdgeDetection);
    trek::serialize(stream, mLsb);
    trek::serialize(stream, mAlmostFull);
    trek::serialize(stream, mControl);
    trek::serialize(stream, mStatus);
    trek::serialize(stream, mDeadTime);
    trek::serialize(stream, mEventBLT);
}

void Settings::deserialize(std::istream& stream) {
    trek::deserialize(stream, mTriggerMode);
    trek::deserialize(stream, mTriggerSubtraction);
    trek::deserialize(stream, mTdcMeta);
    trek::deserialize(stream, mWindowWidth);
    trek::deserialize(stream, mWindowOffset);
    trek::deserialize(stream, mEdgeDetection);
    trek::deserialize(stream, mLsb);
    trek::deserialize(stream, mAlmostFull);
    trek::deserialize(stream, mControl);
    trek::deserialize(stream, mStatus);
    trek::deserialize(stream, mDeadTime);
    trek::deserialize(stream, mEventBLT);

}

void Settings::setTriggerMode(bool flag) {
    mTriggerMode = static_cast<uint8_t>(flag);
}

void Settings::setTriggerSubtraction(bool flag) {
    mTriggerSubtraction = static_cast<uint8_t>(flag);
}

void Settings::setTdcMeta(bool flag) {
    mTdcMeta = static_cast<uint8_t>(flag);
}

void Settings::setWindowWidth(uint16_t width) {
    mWindowWidth = width;
}

void Settings::setWindowOffset(int16_t offset) {
    mWindowOffset = offset;
}

void Settings::setEdgeDetection(EdgeDetection detection) {
    mEdgeDetection = detection;
}

void Settings::setLsb(Lsb lsb) {
    mLsb = lsb;
}

void Settings::setAlmostFull(uint16_t almostFull) {
    mAlmostFull = almostFull;
}

void Settings::setControlRegister(uint16_t reg) {
    mControl = reg;
}

void Settings::setStatusRegister(uint16_t reg) {
    mStatus = reg;
}

void Settings::setDeadTime(uint16_t deadTime) {
    mDeadTime = deadTime;
}

void Settings::setEventBLT(uint16_t eventBLT) {
    mEventBLT = eventBLT;
}

bool Settings::getTriggerMode() const {
    return static_cast<bool>(mTriggerMode);
}

bool Settings::getTriggerSubtraction() const {
    return static_cast<bool>(mTriggerSubtraction);
}

bool Settings::getTdcMeta() const {
    return static_cast<bool>(mTdcMeta);
}

uint16_t Settings::getWindowWidth() const {
    return mWindowWidth;
}

int16_t Settings::getWindowOffset() const {
    return mWindowOffset;
}

EdgeDetection Settings::getEdgeDetection() const {
    return mEdgeDetection;
}

Lsb Settings::getLsb() const {
    return mLsb;
}

uint16_t Settings::getAlmostFull() const {
    return mAlmostFull;
}

uint16_t Settings::getControl() const {
    return mControl;
}

uint16_t Settings::getStatus() const {
    return mStatus;
}

uint16_t Settings::getDeadTime() const {
    return mDeadTime;
}

uint16_t Settings::getEventBLT() const {
    return mEventBLT;
}

} //data
} //trek
