#pragma once
#include "line2.hpp"
#include "line3.hpp"

namespace trek {
namespace math {


class CoordSystem3 {
public:
	CoordSystem3(const Vec3& offset, const Vec3& X,const Vec3& Y, const Vec3& Z);
	void convertTo(Vec3& vec) const;
	void convertTo(Line3& line) const;
protected:
	void rotate(Vec3& vec) const;
	void shift(Vec3& vec) const;
private:
	Vec3 mOffset;
	Vec3 V1;
	Vec3 V2;
	Vec3 V3;
};

} //math
} //trek
