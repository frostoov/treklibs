#include "hitrecord.hpp"

#include <trek/common/serialization.hpp>

namespace trek {
namespace data {

using std::istream;
using std::ostream;

HitRecord::HitRecord(unsigned wire, unsigned chamber, unsigned time)
	: mChannel( uint16_t((wire&0xFF) | (chamber<<8))),
	  mTime(time) { }

HitRecord::HitRecord(std::istream &stream) {
	this->deserialize(stream);
}

unsigned HitRecord::wire() const {
	return unsigned(mChannel & 0xFF);
}

unsigned HitRecord::chamber() const {
	return unsigned(mChannel >> 8);
}

unsigned int HitRecord::time() const {
	return unsigned(mTime);
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