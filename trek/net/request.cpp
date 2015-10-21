#include "request.hpp"

namespace trek {
namespace net {

using nlohmann::json;

Request::Request(const JsonString& object,
                 const JsonString& method,
                 const JsonArray& inputs)
	: mObject(object),
	  mMethod(method),
	  mInputs(inputs) { }

Request::Request(const std::string& request) {
	auto jsonRequest = json::parse(request);
	mObject = jsonRequest.at("object").get<JsonString>();
	mMethod = jsonRequest.at("method").get<JsonString>();
	mInputs = jsonRequest.at("inputs").get<JsonArray>();
}

Request::operator std::string() const {
	return json{
		{"object", mObject},
		{"method", mMethod},
		{"inputs", mInputs},
	} .dump();
}


const Request::JsonString& Request::object() const {
	return mObject;
}

const Request::JsonString& Request::method() const {
	return mMethod;
}

const Request::JsonArray& Request::inputs() const {
	return mInputs;
}

} //net
} //trek
