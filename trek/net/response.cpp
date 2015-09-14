#include "response.hpp"

namespace trek {
namespace net {

using nlohmann::json;

Response::Response(const JsonString& object,
                   const JsonString& method,
                   const JsonArray& outputs,
                   const JsonBool& status)
    : mObject(object),
      mMethod(method),
      mOutputs(outputs),
      mStatus(status) { }

Response::Response(const std::string& response) {
    auto jsonResponse = json::parse(response);

    mObject  = jsonResponse.at("object").get<JsonString>();
    mMethod  = jsonResponse.at("method").get<JsonString>();
    mOutputs = jsonResponse.at("outputs").get<JsonArray>();
    mStatus  = jsonResponse.at("status").get<JsonBool>();
}

Response::operator std::string() const{
    return json{
        {"object", mObject},
        {"method", mMethod},
        {"outputs", mOutputs},
        {"status", mStatus},
    }.dump();
}

const Response::JsonString& Response::getObject() const {
    return mObject;
}

const Response::JsonString& Response::getMethod() const {
    return mMethod;
}

const Response::JsonArray& Response::getOutputs() const {
    return mOutputs;
}

const Response::JsonBool& Response::getStatus() const {
    return mStatus;
}



}
}
