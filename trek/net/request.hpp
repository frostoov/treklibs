#ifndef TREK_NET_REQUEST_HPP
#define TREK_NET_REQUEST_HPP

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

    const JsonString& getObject() const;
    const JsonString& getMethod() const;
    const JsonArray&  getInputs() const;
private:
    JsonString  mObject;
    JsonString  mMethod;
    JsonArray   mInputs;
};

} //net
} //trek

#endif //TREK_NET_REQUEST_HPP
