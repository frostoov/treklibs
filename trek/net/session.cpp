#include "session.hpp"
#include "jcontroller.hpp"

#include <trek/common/stringbuilder.hpp>

namespace trek {
namespace net {

using std::string;
using std::array;

Session::Session(const ControllerMap& controllers, TCP::socket&& socket)
    : mControllers(controllers),
      mSocket(std::move(socket)) { }

void Session::run() {
    mOnStart(*this);
    recv();
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

void Session::recv() {
    mSocket.async_receive(boost::asio::buffer(mBuffer), [this](const auto & errCode, auto length) {
        if(!errCode) {
            string requset(mBuffer.data(), length);
            mOnRecv(*this, requset);
            string response;
            try {
                auto& controller = this->getController(requset);
                response = controller.handleRequest(requset);
            } catch(const std::exception& e) {
                response = StringBuilder() << "Invalid query: " << e.what();
            }
            this->send(response);
            this->recv();
        } else {
            mOnClose(*this);
            this->mOnDestroy(this->shared_from_this());
        }
    });
}

void Session::send(const std::string& response) {
    mSocket.async_send(boost::asio::buffer(response), [this, response](const auto & errCode, auto) {
        if(!errCode)
            mOnSend(*this, response);
        else {
            mOnClose(*this);
            this->mOnDestroy(this->shared_from_this());
        }
    });
}

Controller& Session::getController(const std::string& request) {
    auto object = JController::getObject(request);
    return *mControllers.at(object);
}

} //net
} //trek
