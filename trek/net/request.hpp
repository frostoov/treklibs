#pragma once

#include <json.hpp>

namespace trek {
namespace net {

class Request {
    using Json       = nlohmann::json;
    using JsonString = Json::string_t;
    using JsonArray  = Json::array_t;
public:
    Request(const JsonString& object,
            const JsonString& method,
            const JsonArray& inputs);
    Request(const std::string& request);
    explicit operator std::string() const;

    const JsonString& object() const;
    const JsonString& method() const;
    const JsonArray&  inputs() const;
private:
    JsonString  mObject;
    JsonString  mMethod;
    JsonArray   mInputs;
};

} //net
} //trek
