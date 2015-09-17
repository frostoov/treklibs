#ifndef TREK_COMMON_STREAM_SIZE_HPP
#define TREK_COMMON_STREAM_SIZE_HPP

#include <istream>

namespace trek {

std::istream::pos_type getStreamSize(std::istream& stream);

}

#endif //TREK_COMMON_STREAM_SIZE_HPP
