#pragma once

#include <json.hpp>

namespace trek {
namespace net {

class Response {
	using Json       = nlohmann::json;
	using JsonString = Json::string_t;
	using JsonArray  = Json::array_t;
	using JsonBool   = Json::boolean_t;
public:
	Response(const JsonString& object,
	         const JsonString& method,
	         const JsonArray&  outputs,
	         const JsonBool&   status);
	Response(const std::string& response);
	explicit operator std::string() const;

	const JsonString& object() const;
	const JsonString& method() const;
	const JsonArray& outputs() const;
	const JsonBool& status() const;
private:
	JsonString  mObject;
	JsonString  mMethod;
	JsonArray   mOutputs;
	JsonBool    mStatus;
};

} //net
} //trek
