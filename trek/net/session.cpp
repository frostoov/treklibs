#include "session.hpp"
#include "controller.hpp"

#include <trek/common/serialization.hpp>

#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/interprocess/streams/vectorstream.hpp>

namespace trek {
namespace net {

using nlohmann::json;

using boost::asio::async_read;
using boost::asio::async_write;
using boost::asio::buffer;

using std::string;
using std::array;
using std::exception;

using ovectorstream = boost::interprocess::basic_ovectorstream< std::vector<char> >;

Session::Session(const Controllers& controllers, TCP::socket&& socket)
    : mControllers(controllers),
      mSocket(std::move(socket)),
      mRemoteAddress(mSocket.remote_endpoint().address().to_string()) { }

void Session::run() {
    mOnStart(*this);
    recv();
}

std::string Session::remoteAddress() const {
    return mRemoteAddress;
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
    async_read(mSocket, buffer(&mMsgSize, sizeof(mMsgSize)), [this](auto & errCode, auto) {
        try {
            if(errCode) throw errCode;
            mBuffer.resize(mMsgSize);
            this->msgRecv();
            this->recv();
        } catch(...) {
            mOnClose(*this);
            mOnDestroy(this->shared_from_this());
        }
    });
}

void Session::msgRecv() {
    async_read(mSocket, buffer(mBuffer), [&](auto & errCode, auto) {
        try {
            if(errCode) throw errCode;
            auto request = string(mBuffer.data(), mBuffer.size());
            mOnRecv(*this, request);
            this->handleRequest(request);
        } catch(...) {
            mOnClose(*this);
            mOnDestroy(this->shared_from_this());
        }
    });
}

void Session::send(const string& response) {
    ovectorstream stream;
    trek::serialize(stream, uint64_t(response.size()));
    stream << response;
    async_write(mSocket, buffer(stream.vector()), [this, response](auto & errCode, auto) {
        try {
            if(errCode) throw errCode;
            this->mOnSend(*this, response);
        } catch(...) {
            mOnClose(*this);
            mOnDestroy(this->shared_from_this());
        }
    });
}

void Session::handleRequest(const string& rawRequest) {
    try {
        Request request(rawRequest);
        auto& controller = *mControllers.at(request.object);
        controller.handleRequest(request, [this](const Response & response) {
            this->send(string(response));
        });
    } catch(...) {
        Response response{"unknown", "unknown", {}, "Invalid request"};
        send(string(response));
    }
}

} //net
} //trek
