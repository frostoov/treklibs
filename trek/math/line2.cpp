#include "line2.hpp"

#include <limits>
#include <stdexcept>

namespace trek {
namespace math {

using std::runtime_error;
using std::numeric_limits;
using std::domain_error;

Line2::Line2()
    : k(0), b(0) { }

Line2::Line2(double k_, double b_)
    : k(k_), b(b_) { }

Line2::Line2(const Vec2& dot1, const Vec2& dot2) {
    auto dirVec = dot1 - dot2;
    if(dirVec.x != 0)
        k = dirVec.y / dirVec.x;
    else
        k = numeric_limits<double>::infinity();
    b = dot1.y - k * dot1.x;
}

Line2 Line2::fromVectors(const Vec2& dot, const Vec2& vec) {
    auto k = vec.y / vec.x;
    auto b = dot.y - k * dot.x;
    return Line2{k, b};
}

Vec2 Line2::cross(const Line2& line1, const Line2& line2) {
    if(line1.k == line2.k)
        throw domain_error("Vec2::cross: Lines are parallel");
    if(line1.b != line2.b) {
        auto x = (line1.k - line2.k) / (line2.b - line1.b);
        auto y = line1.k * x + line1.b;
        return {x, y};
    } else
        return {0, 0};
}
}
}
