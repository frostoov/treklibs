#pragma once

#include <functional>

namespace trek {

template<typename T>
class Callback;

template<typename Res, typename ...Args>
class Callback<Res(Args...)> {
	using Function = std::function<Res(Args...)>;
public:

	void operator() (const Args& ...args) {
		if(mFunc != nullptr)
			mFunc(args...);
	}

	const Callback& operator=(const Function& func) const {
		mFunc = func;
		return *this;
	}

	const Callback& operator=(Function&& func) const {
		mFunc = std::move(func);
		return *this;
	}

private:
	mutable Function mFunc;
};

} //trek;
