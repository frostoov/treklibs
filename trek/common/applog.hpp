#ifndef TREK_COMMON_APP_LOG_HPP
#define TREK_COMMON_APP_LOG_HPP

#include "timeprint.hpp"

#include <iostream>
#include <fstream>
#include <functional>

namespace trek {

class AppLog {
    using LogPtr = std::unique_ptr<AppLog>;
    using ostream_function = std::ostream& (*)(std::ostream&);
public:
    AppLog(AppLog&& other) = delete;
    AppLog(const AppLog& other) = delete;
    void operator=(const AppLog& other) = delete;
    void operator=(AppLog&& other) = delete;

    static AppLog& instance();
    static void init(const std::string& logName);

    template<typename T>
    AppLog& operator<<(const T& item) {
        mStream << item;
        if(mStdOut)
            std::cout << item;
        return instance();
    }
    AppLog& operator<<(ostream_function func) {
        mStream << func;
        if(mStdOut)
            std::cout << func;
        return instance();
    }

    void setStdOut(bool flag);
    void flush();
private:
    AppLog(const std::string& logName);
private:
    static LogPtr mInstance;
    std::ofstream mStream;
    bool mStdOut;
};

}

#endif // TREK_COMMON_APP_LOG_HPP
