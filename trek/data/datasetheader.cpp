#include "datasetheader.hpp"

namespace trek {
namespace data {

DataSetHeader::DataSetHeader()
    : mType(DataSetType::Simple) { }

DataSetHeader::DataSetHeader(DataSetType fileType, uint16_t key, Settings settings)
    : mType(fileType), mKey(key), mSettings(settings) { }

DataSetType DataSetHeader::type() const {
    return mType;
}

uint16_t DataSetHeader::key() const {
    return mKey;
}

const Settings& DataSetHeader::settings() const {
    return mSettings;
}

void DataSetHeader::serialize(std::ostream& stream) const {
    trek::serialize(stream, mType);
    trek::serialize(stream, mKey);
    trek::serialize(stream, mSettings);
}

void DataSetHeader::deserialize(std::istream& stream) {
    trek::deserialize(stream, mType);
    trek::deserialize(stream, mKey);
    trek::deserialize(stream, mSettings);
}



} //data
} //trek
