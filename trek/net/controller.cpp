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
	auto method = mMethods.at(request.method);
	return method( request );
}

const string& Controller::name() const {
	return mName;
}

} //net
} //trek
