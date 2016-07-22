#pragma once

#include <trek/net/request.hpp>
#include <trek/net/response.hpp>

#include <unordered_map>
#include <functional>
#include <string>

namespace trek {
namespace net {

class Controller {
protected:
    using BroadcastCb  = std::function<void(const Response&)>;
    using Method       = std::function<Response(const Request&)>;
    using Methods      = std::unordered_map<std::string, Method>;
public:
    Response handleRequest(const Request& request);
    const std::string& name() const;
    void setBroadCast(const BroadcastCb& broadcast) {
        mBroadcast = broadcast;
    }
protected:
    Controller(const std::string& name, const Methods& method);
    void broadcast(const Response& response) {
        if(mBroadcast)
            mBroadcast(response);
    }
private:
    BroadcastCb mBroadcast;
    Methods     mMethods;
    std::string mName;
};

} //net
} //trek
