#include "applog.hpp"

#include "stringbuilder.hpp"

namespace trek {

using std::string;
using std::logic_error;

Log::LogPtr Log::mInstance;

Log::Log(const std::string& logName)
	: mStdOut(false) {
	mStream.exceptions(mStream.failbit | mStream.badbit);
	mStream.open(logName, mStream.binary | mStream.app);
}

Log& Log::instance() {
	if(mInstance == nullptr)
		throw logic_error("Log::instance: app log not init");
	return *mInstance;	
}

void Log::init(const std::string& logName) {
	mInstance.reset(new Log(logName));		
}

void Log::setStdOut(bool flag) {
	mStdOut = flag;
}

void trek::Log::flush() {
	mStream.flush();
}

} //trek
