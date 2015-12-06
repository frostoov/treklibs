#pragma once

#include "hitrecord.hpp"

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <chrono>

namespace trek {
namespace data {

using EventHits = std::vector<HitRecord>;
using ChamHits = std::array<std::vector<unsigned>, 4>;
using TrekHits = std::unordered_map<unsigned, ChamHits>;

/**
 * @class EventRecord
 * @author frostoov
 * @date 03/29/15
 * @file eventrecord.hpp
 * @brief Запись события TDC
 */
class EventRecord {
	using SystemClock  = std::chrono::high_resolution_clock;
	using TimePoint    = SystemClock::time_point;
public:
	EventRecord();
	EventRecord(unsigned nRun, unsigned nEvent, const EventHits& hits);
	EventRecord(std::istream& stream);

	auto begin() {
		return mHits.begin();
	}
	auto begin() const {
		return mHits.begin();
	}
	auto end() {
		return mHits.end();
	}
	auto end() const {
		return mHits.end();
	}
	const HitRecord& operator[](size_t i) const;
	uint64_t nRun() const;
	uint64_t nEvent() const;
	TimePoint time() const;

	auto size() const {
		return mHits.size();
	}
	auto empty() const {
		return mHits.empty();
	}
	/**
	 * @brief Создание и получение ассоциативного массива с измерениями со всей установки.
	 * @return Ассоциативный массив(std::unordered_map) с данными камер
	 */
	TrekHits getTrekHits() const;
	/**
	 * @brief Создание и получение массива с измерениями с камеры
	 * @param cham Номер камеры
	 */
	ChamHits getChamberHits(unsigned cham) const;
	/**
	 * @brief Создать и получить множество номеров сработавших камер
	 * @return Множество номеров сработавших камер
	 */
	std::unordered_set<unsigned> getTriggeredChambers() const;
	/**
	 * @brief Установить данные события
	 * @param data вектор со словами - проволка/камера + время
	 */
	void setHits(const EventHits& data);
	void clearHits();
	void serialize(std::ostream& stream) const;
	void deserialize(std::istream& stream);

protected:
	void serializeTime(std::ostream& stream, const TimePoint& time) const;
	void deserializeTime(std::istream& stream, TimePoint& time);
private:
	uint64_t mNRun;
	uint64_t mNEvent;
	TimePoint mTimePoint;
	EventHits mHits;

};

} //data
} //trek
