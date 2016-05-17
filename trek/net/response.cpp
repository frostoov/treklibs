#include <trek/net/response.hpp>

namespace trek {
namespace net {

using nlohmann::json;

Response::Response(const JsonString& object,
                   const JsonString& method,
                   const JsonArray& outputs,
                   JsonString status)
    : object(object),
      method(method),
      outputs(outputs),
      status(status) { }

Response::Response(const std::string& response) {
    auto jsonResponse = json::parse(response);

    object  = jsonResponse.at("object").get<JsonString>();
    method  = jsonResponse.at("method").get<JsonString>();
    outputs = jsonResponse.at("outputs").get<JsonArray>();
    status  = jsonResponse.at("status").get<JsonString>();
}

Response::operator std::string() const {
    return json{
        {"object",  object},
        {"method",  method},
        {"outputs", outputs},
        {"status",  status},
    } .dump();
}

}
}
