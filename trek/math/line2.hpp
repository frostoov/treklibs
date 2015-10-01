#pragma once

#include "vec2.hpp"

namespace trek {
namespace math {

class Line2 {
public:
    Line2();
    Line2(double k, double b);
    Line2(const Vec2& dot1, const Vec2& dot2);

    double& k() {
        return koefK;
    }
    double& b() {
        return koefB;
    }

    double k() const {
        return koefK;
    }
    double b() const {
        return koefB;
    }

    static Vec2 getIntersection(const Line2& line1, const Line2& line2);
private:
    double koefK;
    double koefB;
};


} //math
} //trek
