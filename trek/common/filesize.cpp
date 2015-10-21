#include "filesize.hpp"

namespace trek {

using std::istream;

istream::pos_type getStreamSize(istream& stream) {
    auto position = stream.tellg();
    stream.seekg(0, stream.end);
    auto size = stream.tellg();
    stream.seekg(position);
    return size;
}

}
