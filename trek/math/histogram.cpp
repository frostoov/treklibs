#include "histogram.hpp"

namespace trek {
namespace math {

Histogram::Histogram(double bottom, double up, double bin)
    : mBin(0), mUp(0), mBottom(0) {
    setParameters(bottom, up, bin);
}

void Histogram::setParameters(double bottom, double up, double bin) {
    buffer.clear();
    if(bottom > up)
        throw std::runtime_error("Invalid histogram parametres");
    mBottom	= bottom;
    mUp		= up;
    mBin	= bin;
    if(mUp != mBottom && mBin != 0)
        buffer.resize((mUp - mBottom) / mBin + 1);
}
void Histogram::expand(double newUp) {
    mUp = newUp;
    buffer.resize((mUp - mBottom) / mBin + 1);
}
void Histogram::addValue(const double val) {
    buffer.at((val - mBottom) / mBin)++;
}

uintmax_t Histogram::value(size_t i) const {
    return buffer.at(i);
}
double Histogram::range(size_t i) const {
    return mBottom + i * mBin;
}

Histogram::cell Histogram::operator [](size_t n) const {
    return {mBottom + n * mBin, buffer.at(n) };
}
uintmax_t Histogram::maxValue() const {
    uintmax_t max = 0;
    for(auto val : buffer)
        if(max < val)
            max = val;
    return max;
}

double Histogram::maxValueRange() const {
    uintmax_t	max = 0;
    size_type	rangeIndex = 0;
    for(size_t i = 0; i < buffer.size(); ++i)
        if(max < buffer.at(i)) {
            max = buffer.at(i);
            rangeIndex = i;
        }
    return range(rangeIndex);
}
double Histogram::bottom() const	{
    return mBottom;
}
double Histogram::up()  const {
    return mUp;
}
double Histogram::bin() const {
    return mBin;
}

Histogram::size_type Histogram::size() const {
    return buffer.size();
}
void Histogram::clear() {
    buffer.clear();
}

void Histogram::free()	{
    buffer.clear();
    buffer.shrink_to_fit();
}

}
}
