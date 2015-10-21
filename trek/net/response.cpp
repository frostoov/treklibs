#include "response.hpp"

namespace trek {
namespace net {

using nlohmann::json;

Response::Response(const JsonString& object,
                   const JsonString& method,
                   const JsonArray& outputs,
                   const JsonBool& status)
	: mObject(object),
	  mMethod(method),
	  mOutputs(outputs),
	  mStatus(status) { }

Response::Response(const std::string& response) {
	auto jsonResponse = json::parse(response);

	mObject  = jsonResponse.at("object").get<JsonString>();
	mMethod  = jsonResponse.at("method").get<JsonString>();
	mOutputs = jsonResponse.at("outputs").get<JsonArray>();
	mStatus  = jsonResponse.at("status").get<JsonBool>();
}

Response::operator std::string() const {
	return json{
		{"object", mObject},
		{"method", mMethod},
		{"outputs", mOutputs},
		{"status", mStatus},
	} .dump();
}

const Response::JsonString& Response::object() const {
	return mObject;
}

const Response::JsonString& Response::method() const {
	return mMethod;
}

const Response::JsonArray& Response::outputs() const {
	return mOutputs;
}

const Response::JsonBool& Response::status() const {
	return mStatus;
}



}
}
