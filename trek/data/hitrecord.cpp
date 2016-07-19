#include "hitrecord.hpp"

#include <trek/common/serialization.hpp>

namespace trek {
namespace data {

using std::istream;
using std::ostream;

HitRecord::HitRecord(Type type, unsigned wire, unsigned chamber, unsigned time)
    : mChannel( uint32_t(type) << 28 | ((chamber & 0xFFFFF) << 8) | (wire & 0xFF)),
      mTime(time) { }

HitRecord::HitRecord(std::istream& stream) {
    this->deserialize(stream);
}

uint32_t HitRecord::wire() const {
    return unsigned(mChannel & 0xFF);
}

uint32_t HitRecord::chamber() const {
    return unsigned((mChannel >> 8) & 0xFFFFF);
}

uint32_t HitRecord::time() const {
    return unsigned(mTime);
}

HitRecord::Type HitRecord::type() const {
    return Type(mChannel >> 28);
}

void HitRecord::serialize(ostream& stream) const {
    trek::serialize(stream, mChannel);
    trek::serialize(stream, mTime);
}

void HitRecord::deserialize(istream& stream) {
    trek::deserialize(stream, mChannel);
    trek::deserialize(stream, mTime);
}

}
}
