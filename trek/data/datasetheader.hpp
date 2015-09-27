#pragma once

#include "tdcsettings.hpp"

#include <trek/common/serialization.hpp>

namespace trek {
namespace data {

enum class DataSetType : uint16_t {
    Simple = 0,
    Uragan = 1,
    Ctudc  = 2,
};

using DataSetTypeContainer = EnumContainer<DataSetType, uint16_t>;

struct DataSetHeader {
public:
    DataSetHeader();
    DataSetHeader(DataSetType fileType, uint16_t key, Settings settings);

    DataSetType type() const;
    uint16_t key() const;
    const Settings& settings() const;

    void serialize(std::ostream& stream) const;
    void deserialize(std::istream& stream);
    static constexpr size_t getSize() {
        return trek::getSize<decltype(mType) >() + trek::getSize<decltype(mKey) >() +
               trek::getSize<decltype(mSettings) >();
    }
private:
    DataSetTypeContainer mType;	/*!< Тип файла */
    uint16_t             mKey;		/*!< Контрольное поле */
    Settings             mSettings;	/*!< Настройки TDC, при которых осуществлялся набор */
};

} //data
} //trek
