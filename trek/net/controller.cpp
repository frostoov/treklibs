#include "controller.hpp"

namespace trek {
namespace net {

using std::string;
using std::runtime_error;

using nlohmann::json;

Controller::Controller(const string& name, const Methods& methods)
    : mMethods(methods),
      mName(name) {
    mMethods.emplace("listMethods", [&](auto&) {
        json::array_t methodsList;
        for(auto& m : mMethods) {
            methodsList.push_back(m.first);
        }
        return Response(this->name(), "listMethods", methodsList);
    });
}

Response Controller::handleRequest(const Request& request) {
    try {
        auto method = mMethods.at(request.method);
        return method(request);
    } catch(std::exception& e) {
        return {request.object, request.method, {}, e.what()};
    }
}

const string& Controller::name() const {
    return mName;
}

} //net
} //trek
