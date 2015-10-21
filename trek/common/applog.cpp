#include "applog.hpp"

#include "assertion.hpp"
#include "stringbuilder.hpp"

namespace trek {

using std::string;

Log::LogPtr Log::mInstance;

Log::Log(const std::string& logName)
	: mStdOut(false) {
	mStream.exceptions(mStream.failbit | mStream.badbit);
	mStream.open(logName, mStream.binary | mStream.app);
}

Log& Log::instance() {
	if(mInstance)
		return *mInstance;
	else
		throw Assertion("Log::instance: app log not init");
}

void Log::init(const std::string& logName) {
	if(mInstance == nullptr)
		mInstance.reset(new Log(logName));
	else
		throw Assertion("Log::init: app log is already init");
}

void Log::setStdOut(bool flag) {
	mStdOut = flag;
}

void trek::Log::flush() {
	mStream.flush();
}

} //trek
