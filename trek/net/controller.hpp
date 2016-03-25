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
	using SendCallback = std::function<void(const Response&)>;
	using Method       = std::function<void(const Request&, const SendCallback&)>;
	using Methods      = std::unordered_map<std::string, Method>;
public:
	void handleRequest(const Request& request, const SendCallback& send);
	const std::string& name() const;
	void setBroadCast(const SendCallback& broadcast) {
		mBroadcast = broadcast;
	}
protected:
	Controller(const std::string& name, const Methods& method);
	void broadcast(const Response& response) {
		if(mBroadcast)
			mBroadcast(response);
	}
	SendCallback mBroadcast;
private:
	Methods     mMethods;
	std::string mName;
};

} //net
} //trek
