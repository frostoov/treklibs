#ifndef ASSERTION_HPP
#define ASSERTION_HPP

#include <string>

namespace trek {

class Assertion {
public:
    Assertion(const std::string& message)
        : mMessage(message) { }
    Assertion(std::string&& message)
        : mMessage( std::move(message) ) { }

    operator std::string() {
        return mMessage;
    }

private:
    std::string mMessage;
};

} //trek

#endif //ASSERTION_HPP
