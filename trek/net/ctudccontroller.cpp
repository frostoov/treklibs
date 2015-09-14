#include "ctudccontroller.hpp"

namespace trek {
namespace net {

using std::string;
using std::runtime_error;

using nlohmann::json;

CtudcController::CtudcController(const Methods& method)
    : mMethods(method) { }

std::string CtudcController::handleRequest(const std::string& rawRequest) {
    Lock lock(mMutex);
    Request request(rawRequest);
    auto method = getMethod(request);
    return string( method( request ) );
}

string CtudcController::getObject(const std::string& rawRequest) {
    return Request(rawRequest).getObject();
}

CtudcController::Method CtudcController::getMethod(const Request& request) const {
    if(request.getObject() == getName())
        return mMethods.at(request.getMethod());
    else
        throw runtime_error("Invalid request object");
}

} //net
} //trek
