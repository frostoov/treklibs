#pragma once

#include <trek/common/serialization.hpp>

#include <cstdint>

namespace trek {
namespace data {

struct DateTime {
    uint8_t hsecond;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;

    void serialize(std::ostream& stream) const {
        trek::serialize(stream, hsecond);
        trek::serialize(stream, second);
        trek::serialize(stream, minute);
        trek::serialize(stream, hour);
        trek::serialize(stream, day);
        trek::serialize(stream, month);
        trek::serialize(stream, year);
    }
    void deserialize(std::istream& stream) {
        trek::deserialize(stream, hsecond);
        trek::deserialize(stream, second);
        trek::deserialize(stream, minute);
        trek::deserialize(stream, hour);
        trek::deserialize(stream, day);
        trek::deserialize(stream, month);
        trek::deserialize(stream, year);
    }
};

struct NevodPackage {
    int8_t   keyword[6];        //Ключевое слово сообщения "TRACK "
    uint16_t type;              //тип сообщения 0 - простая метка
    DateTime dateTime;          //Время события по локальным часам ЦМ НЕВОД
    uint32_t numberOfRun;       //номер рана
    uint32_t numberOfRecord;     //номер события
    uint32_t statusRegister;    //Статусный регистр "TrC" без купюр
    uint16_t nvdTriggerType;    //Тип триггера НЕВОД + СКТ
    uint16_t decorTriggerType;  //Тип триггера ДЕКОР
    int16_t  fifoNumber;        //Количество сработавших КСМ по триггеру С
    //У скольких КСМ есть хоть какие данные в FIFO
    void serialize(std::ostream& stream) const {
        trek::serialize(stream, keyword, sizeof(keyword));
        trek::serialize(stream, type);
        trek::serialize(stream, dateTime);
        trek::serialize(stream, numberOfRun);
        trek::serialize(stream, numberOfRecord);
        trek::serialize(stream, statusRegister);
        trek::serialize(stream, nvdTriggerType);
        trek::serialize(stream, decorTriggerType);
        trek::serialize(stream, fifoNumber);
    }
    void deserialize(std::istream& stream) {
        trek::deserialize(stream, keyword, sizeof(keyword));
        trek::deserialize(stream, type);
        trek::deserialize(stream, dateTime);
        trek::deserialize(stream, numberOfRun);
        trek::deserialize(stream, numberOfRecord);
        trek::deserialize(stream, statusRegister);
        trek::deserialize(stream, nvdTriggerType);
        trek::deserialize(stream, decorTriggerType);
        trek::deserialize(stream, fifoNumber);
    }
};

} //data
} //trek
