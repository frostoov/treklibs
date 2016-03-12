#pragma once

#include "controller.hpp"

#include <trek/common/callback.hpp>

#include <boost/asio/ip/tcp.hpp>

#include <string>
#include <array>
#include <unordered_map>

namespace trek {
namespace net {

class Session : public std::enable_shared_from_this<Session> {
	using Buffer = std::vector<char>;
	using Controllers   = std::unordered_map< std::string, std::shared_ptr<Controller> >;
public:
	using DestroyCallback = Callback<void(const std::shared_ptr<Session>&)>;
	using MessageCallback = Callback<void(const Session&, const std::string message)>;
	using StatusCallback = Callback<void(const Session&)>;
	using TCP = boost::asio::ip::tcp;
public:
	Session(const Controllers& controllers, TCP::socket&& socket);
	void run();
	std::string getRemoteAddress() const;

public: //callbacks
	const MessageCallback& onRecv();
	const MessageCallback& onSend();

	const StatusCallback& onStart();
	const StatusCallback& onClose();
	const DestroyCallback& onDestroy();
protected:
	void recv();
	void send(const std::string& response);

	void msgRecv();
	void msgSend(const std::string& response);

	Response handleRequest(const std::string& rawRequest);
private:
	Controllers mControllers;
	TCP::socket mSocket;

	MessageCallback mOnRecv;
	MessageCallback mOnSend;
	StatusCallback mOnStart;
	StatusCallback mOnClose;
	DestroyCallback mOnDestroy;

	Buffer mBuffer;
	uint64_t mMsgSize;
	std::string mRemoteAddress;
};

} //net
} //trek
