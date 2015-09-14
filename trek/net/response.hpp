#ifndef TREK_NET_RESPONSE_HPP
#define TREK_NET_RESPONSE_HPP

#include <json.hpp>

namespace trek {
namespace net {

class Response {
    using Json       = nlohmann::json;
    using JsonString = Json::string_t;
    using JsonArray  = Json::array_t;
    using JsonBool   = Json::boolean_t;
public:
    Response(const JsonString& getObject,
             const JsonString& getMethod,
             const JsonArray&  getOutputs,
             const JsonBool&   getStatus);
    Response(const std::string& response);
    explicit operator std::string() const;

    const JsonString& getObject() const;
    const JsonString& getMethod() const;
    const JsonArray& getOutputs() const;
    const JsonBool& getStatus() const;
private:
    JsonString  mObject;
    JsonString  mMethod;
    JsonArray   mOutputs;
    JsonBool    mStatus;
};

} //net
} //trek

#endif //TREK_NET_RESPONSE_HPP
