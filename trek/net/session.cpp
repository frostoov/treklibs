#include "session.hpp"
#include "ctudccontroller.hpp"

#include <trek/common/stringbuilder.hpp>

namespace trek {
namespace net {

using std::string;
using std::array;

Session::Session(const ControllerMap& controllers, boost::asio::ip::tcp::socket&& socket)
    : mControllers(controllers),
      mSocket(std::move(socket)) { }

void Session::start() {
    mOnStart(*this);
    doRecieve();
}

std::string Session::getRemoteAddress() const {
    return mSocket.remote_endpoint().address().to_string();
}

const Session::MessageCallback& Session::onRecv() {
    return mOnRecv;
}

const Session::MessageCallback& Session::onSend() {
    return mOnSend;
}

const Session::StatusCallback& Session::onStart() {
    return mOnStart;
}

const Session::StatusCallback& Session::onClose() {
    return mOnClose;
}

const Session::DestroyCallback& Session::onDestroy() {
    return mOnDestroy;
}

void Session::doRecieve() {
    mSocket.async_receive(boost::asio::buffer(mBuffer), [this](const auto& errCode, auto length) {
        if(!errCode) {
            string requset(mBuffer.data(), length);
            mOnRecv(*this, requset);
            string response;
            try {
                auto& controller = getController(requset);
                response = controller.handleRequest(requset);
            } catch(const std::exception& e) {
                response = StringBuilder() << "Invalid query " << e.what();
            }
            doSend(response);
            doRecieve();
        } else {
            mSocket.close();
            mOnClose(*this);
            mOnDestroy(shared_from_this());
        }
    });
}

void Session::doSend(const std::string& response) {
    mSocket.async_send(boost::asio::buffer(response), [this, response](const auto& errCode, auto) {
        if(!errCode)
            mOnSend(*this, response);
        else {
            mOnClose(*this);
            mOnDestroy(shared_from_this());
        }
    });
}

Controller& Session::getController(const std::string request) {
    auto object = CtudcController::getObject(request);
    return *mControllers.at(object);
}

} //net
} //trek
