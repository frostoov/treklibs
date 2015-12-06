#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>
#include <stdexcept>

namespace trek {
namespace math {

class Histogram {
    using vector    = std::vector<uintmax_t>;
    using size_type = vector::size_type;
public:
    using cell = std::pair<double, uintmax_t>;

    Histogram(double bottom, double up, double bin);
    void setParameters(double bottom, double up, double bin);
    void expand(double newUp);
    void addValue(double val);
    uintmax_t value(size_t i) const;
    double range(size_t i) const;
    cell operator [](size_t n) const;
    uintmax_t maxValue() const;

    double maxValueRange() const;
    double bottom() const;
    double up()  const;
    double bin() const;

    size_type size() const;
    void clear();
    void free();
private:
    vector buffer;
    double mBin;
    double mUp;
    double mBottom;
};

} //mmath
} //trek
