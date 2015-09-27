#pragma once

#include "controller.hpp"
#include "request.hpp"
#include "response.hpp"

#include <functional>
#include <unordered_map>
#include <mutex>

namespace trek {
namespace net {

class JController : public Controller {
    using Mutex = std::mutex;
    using Lock  = std::lock_guard<Mutex>;
protected:
    using Method  = std::function<Response(const Request&)>;
    using Methods = std::unordered_map<std::string, Method>;
public:
    std::string handleRequest(const std::string& rawRequest) override;
    static std::string getObject(const std::string& rawRequest);
protected:
    JController(const Methods& method);
private:
    Method  getMethod(const Request& request) const;
    Methods mMethods;
    Mutex   mMutex;
};

} //net
} //trek
