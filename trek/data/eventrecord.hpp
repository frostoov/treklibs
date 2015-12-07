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
/*!
 * \brief Массив с измерениями камеры
 * Индекс массива - номер проволки (нумерация с 0), значение - вектор измерений с проволки
 */
using ChamHits = std::array<std::vector<unsigned>, 4>;
/*!
 * \brief Ассоциативынй массив с измерениями всей установки
 * Ключ массив - номер камеры (нумерация с 0), значение - массив с измерениями камеры(ChamHits)
 */
using TrekHits = std::unordered_map<unsigned, ChamHits>;

/*!
 * \class EventRecord
 * \author frostoov
 * \date 03/29/15
 * \file eventrecord.hpp
 * \brief Запись события TDC
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
	/*!
	 * \brief Номер рана (неводский)
	 */
	uint64_t nRun() const;
	/*!
	 * \brief Номер события (неводский)
	 */
	uint64_t nEvent() const;
	/*!
	 * \brief Время записи события
	 */
	TimePoint time() const;

	/*!
	 * \brief Количество хитов в событии
	 */
	auto size() const {
		return mHits.size();
	}
	auto empty() const {
		return mHits.empty();
	}
	/*!
	 * \brief Создание и получение ассоциативного массива с измерениями со всей установки.
	 */
	TrekHits getTrekHits() const;
	/*!
	 * \brief Создание и получение массива с измерениями с камеры
	 * \param[cham] Номер камеры
	 */
	ChamHits getChamberHits(unsigned cham) const;
	/*!
	 * \brief Создание и получение множества номеров сработавших камер
	 */
	std::unordered_set<unsigned> getTriggeredChambers() const;
	/*!
	 * \brief Установка данных события
	 * \param data вектор со хитами TDC
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
