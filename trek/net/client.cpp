#include "client.hpp"

namespace trek {
namespace net {

using std::string;

Client::Client(const string& ip, uint16_t port)
    : mSocket(mIoService) {
    mSocket.connect({IpAddress::from_string(ip), port});
}

Response Client::sendRequst(const Request& request) {
    mSocket.send( boost::asio::buffer(string(request)) );
    auto size = mSocket.receive(boost::asio::buffer(mBuffer));
    return Response( {mBuffer.data(), size} );
}

}
}
