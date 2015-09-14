#ifndef TREK_COMMON_STRING_BUILDER_HPP
#define TREK_COMMON_STRING_BUILDER_HPP

#include <string>
#include <sstream>

namespace trek {

class StringBuilder {
public:
    template<typename T>
    StringBuilder& operator<< (const T& arg) {
        mStream << arg;
        return *this;
    }
    operator std::string() const {
        return mStream.str();
    }
protected:
    std::ostringstream mStream;
};

}

#endif // TREK_COMMON_STRING_BUILDER_HPP
