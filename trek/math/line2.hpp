#pragma once

#include "vec2.hpp"

namespace trek {
namespace math {

class Line2 {
public:
    Line2();

    Line2(const Vec2& dot1, const Vec2& dot2);

    double& k();
    double& b();

    double k() const;
    double b() const;
    static Vec2 getIntersection(const Line2& line1, const Line2& line2);
private:
    double koefK;
    double koefB;
};


} //math
} //trek
