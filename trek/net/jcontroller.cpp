#include "jcontroller.hpp"

namespace trek {
namespace net {

using std::string;
using std::runtime_error;

using nlohmann::json;

JController::JController(const Methods& method)
	: mMethods(method) { }

std::string JController::handleRequest(const std::string& rawRequest) {
	Lock lock(mMutex);
	Request request(rawRequest);
	auto method = getMethod(request);
	return string( method( request ) );
}

string JController::getObject(const std::string& rawRequest) {
	return Request(rawRequest).object();
}

JController::Method JController::getMethod(const Request& request) const {
	if(request.object() == name())
		return mMethods.at(request.method());
	else
		throw runtime_error("Invalid request object");
}

} //net
} //trek
