#pragma once

#include "request.hpp"
#include "response.hpp"

#include <unordered_map>
#include <functional>
#include <string>

namespace trek {
namespace net {

class Controller {
protected:
	using Method  = std::function<Response(const Request&)>;
	using Methods = std::unordered_map<std::string, Method>;
public:
	Response handleRequest(const Request& request);
	const std::string& name() const;
protected:
	Controller(const std::string& name, const Methods& method);
private:
	Methods     mMethods;
	std::string mName;
};

} //net
} //trek
