#include "controller.hpp"

namespace trek {
namespace net {

using std::string;
using std::runtime_error;

using nlohmann::json;

Controller::Controller(const string& name, const Methods& method)
	: mMethods(method),
	  mName(name) { }

Response Controller::handleRequest(const Request& request) {
	Lock lock(mMutex);
	auto method = getMethod(request);
	return method( request );
}

Controller::Method Controller::getMethod(const Request& request) const {
	return mMethods.at(request.method());
}

const string& Controller::name() const {
	return mName;
}

} //net
} //trek
