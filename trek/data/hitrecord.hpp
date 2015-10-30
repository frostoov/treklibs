#pragma once

#include <cstdint>
#include <iosfwd>

namespace trek {
namespace data {

class HitRecord {
public:
	HitRecord(unsigned wire, unsigned chamber, unsigned time);
	HitRecord(std::istream& stream);
	unsigned wire() const;
	unsigned chamber() const;
	unsigned time() const;
	
	void serialize(std::ostream& stream) const;
	void deserialize(std::istream& stream);
private:
	uint32_t mChannel;
	uint32_t mTime;
};

} //data
} //trek