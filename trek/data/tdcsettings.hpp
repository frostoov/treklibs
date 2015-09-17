#ifndef TREK_DATA_TDC_SETTINGS_HPP
#define TREK_DATA_TDC_SETTINGS_HPP

#include <trek/common/enumcontainer.hpp>

#include <cstdint>

namespace trek {
namespace data {

enum class Lsb : uint16_t {
    ps800 = 0, ps200 = 1, ps100 = 2
};

enum class EdgeDetection : uint16_t {
    trailing = 1, leading  = 2, trailingLeading = 3
};

using LsbContainer           = EnumContainer<Lsb, uint16_t>;
using EdgeDetectionContainer = EnumContainer<EdgeDetection, uint16_t>;

class Settings {
public:
    Settings();
    bool operator == (const Settings& other);
    bool operator != (const Settings& other);

    void serialize(std::ostream& stream) const;
    void deserialize(std::istream& stream);
    static constexpr size_t getSize();

    void setTriggerMode(bool flag);
    void setTriggerSubtraction(bool flag);
    void setTdcMeta(bool flag);
    void setWindowWidth(uint16_t width);
    void setWindowOffset(int16_t offset);
    void setEdgeDetection(EdgeDetection detection);
    void setLsb(Lsb lsb);
    void setAlmostFull(uint16_t almostFull);
    void setControlRegister(uint16_t reg);
    void setStatusRegister(uint16_t reg);
    void setDeadTime(uint16_t deadTime);
    void setEventBLT(uint16_t eventBlt);

    bool triggerMode() const;
    bool triggerSubtraction() const;
    bool tdcMeta() const;
    uint16_t windowWidth() const;
    int16_t windowOffset() const;
    EdgeDetection edgeDetection() const;
    Lsb lsb() const;
    uint16_t almostFull() const;
    uint16_t control() const;
    uint16_t status() const;
    uint16_t deadTime() const;
    uint16_t eventBlt() const;
private:
    uint8_t	      mTriggerMode;	 /*!< Триггерный режим */
    uint8_t	      mTriggerSubtraction;	 /*!< Trigger subtraction */
    uint8_t	      mTdcMeta;	     /*!< Дополнительные слова с TDC */
    uint16_t      mWindowWidth;	 /*!< Ширина окна в нс */
    int16_t       mWindowOffset;	 /*!< Сдвиг окна в нс */
    EdgeDetectionContainer mEdgeDetection; /*!< Тип измерения */
    LsbContainer mLsb;		     /*!< Разрешение измерения */
    uint16_t      mAlmostFull;	 /*!< Значение регистра almostFull */
    uint16_t      mControl;	     /*!< Значение регистра control */
    uint16_t      mStatus;		 /*!< Значение регистра status */
    uint16_t      mDeadTime;	 /*!< Значение регистра deadTime */
    uint16_t      mEventBLT;	 /*!< Выравнивание событий при BLT считывании */
};

constexpr size_t Settings::getSize() {
    return trek::getSize<decltype(mTriggerMode) >()  + trek::getSize<decltype(mTriggerSubtraction) >() +
           trek::getSize<decltype(mTdcMeta) >()   + trek::getSize<decltype(mWindowWidth) >() +
           trek::getSize<decltype(mWindowOffset) >() + trek::getSize<decltype(mEdgeDetection) >() +
           trek::getSize<decltype(mLsb) >()       + trek::getSize<decltype(mAlmostFull) >() +
           trek::getSize<decltype(mControl) >()   + trek::getSize<decltype(mStatus) >() +
           trek::getSize<decltype(mDeadTime) >();
}

} //data
} //trek

#endif // TREK_DATA_TDC_SETTINGS_HPP
