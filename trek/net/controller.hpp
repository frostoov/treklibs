#ifndef TREK_NET_CONTROLLER_HPP
#define TREK_NET_CONTROLLER_HPP

#include <string>

namespace trek {
namespace net {

class Controller {
public:
    virtual ~Controller() = default;
    virtual std::string handleRequest(const std::string& request) = 0;
    virtual const std::string& getName() const = 0;
protected:
    Controller() = default;
};

} //net
} //trek

#endif //TREK_NET_CONTROLLER_HPP
