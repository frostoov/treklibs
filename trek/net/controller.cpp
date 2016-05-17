#include "controller.hpp"

namespace trek {
namespace net {

using std::string;
using std::runtime_error;

using nlohmann::json;

Controller::Controller(const string& name, const Methods& method)
    : mMethods(method),
      mName(name) { }

void Controller::handleRequest(const Request& request, const SendCallback& send) {
    try {
        auto method = mMethods.at(request.method);
        method(request, send);
    } catch(std::exception& e) {
        Response response{request.object, request.method, {}, e.what()};
        send(string(response));
    }
}

const string& Controller::name() const {
    return mName;
}

} //net
} //trek
