#pragma once

#include "serialization.hpp"

namespace trek {

template<typename E, typename V>
class EnumContainer {
public:
	using Enum  = E;
	using Value = V;
	using Container = EnumContainer<Enum, Value>;
	EnumContainer(const Enum& type)
		: mType(type) { }
	EnumContainer& operator = (const Enum& type) {
		mType = type;
		return *this;
	}
	bool operator == (const Container& container) const {
		return mType == container;
	}
	bool operator != (const Container& container) const {
		return mType != container;
	}
	operator Enum() const {
		return mType;
	}
	operator Value() const {
		return static_cast<Value>(mType);
	}

	void serialize(std::ostream& stream) const {
		trek::serialize(stream, static_cast<Value>(mType));
	}
	void deserialize(std::istream& stream) {
		Value value;
		trek::deserialize(stream, value);
		mType = static_cast<Enum>(value);
	}
	static constexpr size_t getSize() {
		return trek::getSize<Value>();
	}
private:
	Enum mType;
};

}
