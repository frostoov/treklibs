#include "filesize.hpp"

#include "stringbuilder.hpp"

#include <sys/stat.h>
#include <cstring>
#include <cerrno>
#include <stdexcept>

namespace trek {

using std::string;
using std::runtime_error;

off_t getFileSize(const string& fileName) {
    struct stat st;
    if( stat(fileName.data(), &st) == -1)
        throw runtime_error(StringBuilder() << "getFileSize: " << std::strerror(errno));

    return st.st_size;
}

}
