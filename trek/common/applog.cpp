#include "applog.hpp"

#include "assertion.hpp"
#include "stringbuilder.hpp"

namespace trek {

using std::string;

AppLog::AppLog(const std::string& logName)
    : mStdOut(false) {
    mStream.exceptions(mStream.failbit | mStream.badbit);
    mStream.open(logName, mStream.binary | mStream.app);
}

AppLog& AppLog::instance() {
    if(mInstance)
        return *mInstance;
    else
        throw Assertion("AppLog::instance: app log not init");
}

void AppLog::init(const std::string& logName) {
    if(mInstance == nullptr)
        mInstance.reset(new AppLog(logName));
    else
        throw Assertion("AppLog::init: app log is already init");
}

void AppLog::setStdOut(bool flag) {
    mStdOut = flag;
}

void trek::AppLog::flush() {
    mStream.flush();
}

} //trek
