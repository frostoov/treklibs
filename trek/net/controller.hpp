#pragma once

#include <string>

namespace trek {
namespace net {

class Controller {
public:
	virtual ~Controller() = default;
	virtual std::string handleRequest(const std::string& request) = 0;
	virtual const std::string& name() const = 0;
protected:
	Controller() = default;
};

} //net
} //trek
