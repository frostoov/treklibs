#include "line2.hpp"

#include <limits>
#include <stdexcept>

namespace trek {
namespace math {

using std::runtime_error;
using std::numeric_limits;

Line2::Line2()
    : koefK(0), koefB(0) { }

Line2::Line2(double k, double b)
    : koefK(k), koefB(b) { }

Line2::Line2(const Vec2& dot1, const Vec2& dot2) {
    auto dirVec = dot1 - dot2;
    if(dirVec.x() != 0)
        koefK = dirVec.y() / dirVec.x();
    else {
        koefK = numeric_limits<double>::infinity();
    }
    koefB = dot1.y() - koefK * dot1.x();
}


Vec2 Line2::getIntersection(const Line2& line1, const Line2& line2) {
    if(line1.k() == line2.k())
        throw runtime_error("Vec2::getIntersection: Lines are parallel");
    if(line1.b() != line2.b()) {
        auto x = (line1.k() - line2.k()) / (line2.b() - line1.b());
        auto y = line1.k() * x + line1.b();
        return {x, y};
    } else
        return {0, 0};
}
}
}
