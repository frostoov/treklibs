#pragma once

#include "ctudcrecord.hpp"
#include "datasetheader.hpp"

#include <string>
#include <fstream>
#include <vector>

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
	bool checkStreamState();
private:
	mutable std::ifstream mStream;
	Record mCurrentRecord;
	DataSetHeader mHeader;
	pos_type mStreamSize;
	double mLsbKoef;
	bool   mHasValidRecord;
};

} //data
} //trek
