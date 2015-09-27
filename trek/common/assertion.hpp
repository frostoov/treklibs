#pragma once

#include <string>

namespace trek {

class Assertion {
public:
    Assertion(const std::string& message)
        : mMessage("Assertion: " + message) { }
    Assertion(std::string&& message)
        : mMessage( "Assertion: " +  std::move(message) ) { }

    operator std::string() {
        return mMessage;
    }

private:
    std::string mMessage;
};

} //trek
