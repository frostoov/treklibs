#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>

namespace std {

template<typename Clock, typename Duration>
std::ostream& operator<<(std::ostream& stream, const std::chrono::time_point<Clock, Duration>& tp) {
	auto time = Clock::to_time_t(tp);
	auto lt = std::localtime(&time);
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()).count();
	return stream << std::put_time(lt, "%F %T.") << (us % 1000000) << std::put_time(lt, " %z %Z");
}

}
