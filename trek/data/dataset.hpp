#ifndef TREK_DATA_DATA_SET_HPP
#define TREK_DATA_DATA_SET_HPP

#include <string>
#include <fstream>
#include <vector>

#include "ctudcrecord.hpp"
#include "datasetheader.hpp"

namespace trek {
namespace data {

/**
 * @class DataSet
 * @author
 * @date 03/15/15
 * @file tudataset.hpp
 * @brief Буфер событий
 */

class DataSet {
    using pos_type = std::ifstream::pos_type;
public:
    using Record = CtudcRecord;
public:
    DataSet();
    DataSet(const std::string& path);

    void open(const std::string& path);
    void close();

    const Record& currentRecord() const;
    bool next();

    bool isOpen() const;
    static bool checkExtension(const std::string& fileName);
    operator bool() const;
protected:
    void checkOpen() const;
    void readHeader();
    double lsbKoef(const Settings& settings) const;
    bool isValid(const DataSetHeader& header);
private:
    mutable std::ifstream mStream;
    Record mCurrentRecord;
    DataSetHeader mHeader;
    pos_type mStreamSize;
    double mLsbKoef;
};

} //data
} //trek

#endif // TREK_DATA_DATA_SET_HPP
