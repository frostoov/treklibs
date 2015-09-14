#include "dataset.hpp"

#include <trek/common/assertion.hpp>

using std::string;
using std::istream;
using std::ios;
using std::runtime_error;

namespace trek {
namespace data {

DataSet::DataSet()
    : mStreamSize(0) {
    mStream.exceptions(mStream.badbit | mStream.failbit);
}

DataSet::DataSet(const string& path) {
    open(path);
}

const DataSet::Record& DataSet::getCurrentRecord() const {
    checkOpen();
    return mCurrentRecord;
}

bool DataSet::next() {
    checkOpen();
    if (*this) {
        mCurrentRecord.deserialize(mStream);
        mCurrentRecord.convertTdcWords(mLsbKoef);
        return true;
    } else
        return false;
}

void DataSet::open(const string& path) {
    mStream.open(path, mStream.binary);
    mStreamSize = getStreamSize(mStream);
    readHeader();
    next();
}

void DataSet::close() {
    mStream.close();
}

bool DataSet::isOpen() const {
    return mStream.is_open();
}

bool DataSet::checkExtension(const string& fileName) {
    auto pos = fileName.find_last_of('.');
    return pos != fileName.npos && fileName.substr(pos + 1) == "tds";
}

void DataSet::checkOpen() const {
    if (!isOpen())
        throw Assertion("DataSet stream is not opened!");
}

void DataSet::readHeader() {
    checkOpen();
    if (static_cast<size_t>(mStreamSize) < DataSetHeader::getSize())
        throw runtime_error("DataSet::readHeader: invalid file size");
    deserialize(mStream, mHeader);
    if (!isValid(mHeader))
        throw runtime_error("DataSet::readHeader: invalid header");
    mLsbKoef = getLSBKoef(mHeader.getSettings());
}

double DataSet::getLSBKoef(const Settings& settings) const {
    auto lsb = settings.getLsb();
    if (lsb == Lsb::ps100)
        return 0.098;
    else if (lsb == Lsb::ps200)
        return 0.195;
    else if (lsb == Lsb::ps800)
        return 0.781;
    else
        throw std::runtime_error("DataSet::getLSBKoef: invalude lsb value");
}

bool DataSet::isValid(const DataSetHeader& header) {
    return header.getKey() == 52015 && header.getType() == DataSetType::Ctudc;
}

std::ios::pos_type DataSet::getStreamSize(istream& stream) {
    auto position = stream.tellg();
    stream.seekg(0, stream.end);
    auto size = stream.tellg();
    stream.seekg(position);
    return size;
}

DataSet::operator bool() const {
    return isOpen() && mStream && mStream.tellg() < mStreamSize;
}

} //data
} //trek
