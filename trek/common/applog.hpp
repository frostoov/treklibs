#pragma once

#include "timeprint.hpp"

#include <iostream>
#include <fstream>

namespace trek {

class Log {
    using SystemClock = std::chrono::system_clock;
    using LogPtr = std::unique_ptr<Log>;
    using ostream_function = std::ostream & (*)(std::ostream&);
public:
    Log(Log&& other) = delete;
    Log(const Log& other) = delete;
    void operator=(const Log& other) = delete;
    void operator=(Log&& other) = delete;

    static Log& instance();
    static void init(const std::string& logName);

    template<typename T>
    Log& operator<<(const T& item) {
        mStream << item;
        if(mStdOut)
            std::cout << item;
        return instance();
    }
    Log& operator<<(ostream_function func) {
        mStream << func;
        if(mStdOut)
            std::cout << func;
        return instance();
    }

    void setStdOut(bool flag);
    void flush();
private:
    Log(const std::string& logName);
private:
    static LogPtr mInstance;
    std::ofstream mStream;
    bool mStdOut;
};

}
