#pragma once

#include "request.hpp"
#include "response.hpp"

#include <unordered_map>
#include <functional>
#include <string>
#include <mutex>

namespace trek {
namespace net {

class Controller {
	using Mutex = std::mutex;
	using Lock  = std::lock_guard<Mutex>;
protected:
	using Method  = std::function<Response(const Request&)>;
	using Methods = std::unordered_map<std::string, Method>;
public:
	Response handleRequest(const Request& request);
	const std::string& name() const;
protected:
	Controller(const std::string& name, const Methods& method);
private:
	Method  getMethod(const Request& request) const;
private:
	Methods     mMethods;
	std::string mName;
	Mutex       mMutex;
};

} //net
} //trek
