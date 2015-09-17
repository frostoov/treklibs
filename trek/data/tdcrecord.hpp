#ifndef TREK_DATA_TDC_RECORD_HPP
#define TREK_DATA_TDC_RECORD_HPP

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace trek {
namespace data {

using WordVector = std::vector<uint32_t>;

/**
 * @class TdcRecord
 * @author frostoov
 * @date 03/29/15
 * @file tuevent.hpp
 * @brief Запись события TDC
 */
class TdcRecord {
public:
    using EventTimes	= std::array<WordVector, 4>;
    using TrekEvent		= std::unordered_map<size_t, EventTimes>;
public:
    TdcRecord() = default;
    TdcRecord(std::istream& stream);
    TdcRecord(const WordVector& eventWords);
    /**
     * @brief Возвращает время измерения
     * @param word Слово TDC
     * @return Время в [нс]
     */
    static uint32_t getMesurement(uint32_t word);
    /**
     * @brief Возвращает номер камеры
     * @param word Слово TDC
     * @return Номер камеры
     */
    static uint32_t getChamber(uint32_t word);
    /**
     * @brief Возвращает номер проволки
     * @param word Слово TDC
     * @return Номер проволки
     */
    static uint32_t getWire(uint32_t word);
    /**
     * @brief Получение сырых данных с TDC
     * @return Ссылка на константный вектор со словами TDC - std::vector<uint32_t>
     */
    const WordVector& data() const;
    /**
     * @brief Создание и получение ассоциативного массива с измерениями со всей установки.
     * @return Ассоциативный массив(std::unordered_map) с данными камер
     */
    TrekEvent getTrekEvent() const;
    /**
     * @brief Создание и получение массива с измерениями с камеры
     * @param cham Номер камеры
     */
    EventTimes getChamberEvent(size_t cham) const;
    /**
     * @brief Создать и получить множество номеров сработавших камер
     * @return Множество номеров сработавших камер
     */
    std::unordered_set<uintmax_t> getTriggeredChambers() const;
    /**
     * @brief Установить данные события
     * @param data вектор со словами - проволка/камера + время
     */
    void setTdcData(const WordVector& data);
    /**
     * @brief Очистить данные события
     */
    void convertTdcWords(double koef);
    void clearTdcData();
    void serialize(std::ostream& stream) const;
    void deserialize(std::istream& stream);
private:
    WordVector mTdcWords;		/**< Вектор с сырыми записями. */
};

/**
 * @class AbstractEventHandler
 * @author frostoov
 * @date 03/15/15
 * @file tuevent.hpp
 * @brief Класс, задает интерфейс для обработки TDCRecord-ов
 */
class AbstractEventHandler {
public:
    virtual ~AbstractEventHandler() = default;
    /**
     * @brief Обработка единичного события
     * @param event Событие, которое будет обработано
     */
    virtual void handleEvent(const TdcRecord& TUEvent) = 0;
    /**
     * @brief Завершение обработки данных
     */
    virtual void flush() = 0;
protected:
    AbstractEventHandler() = default;
};

} //data
} //trek

#endif // TREK_DATA_TDC_RECORD_HPP
