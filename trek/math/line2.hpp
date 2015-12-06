#pragma once

#include "vec2.hpp"

namespace trek {
namespace math {

struct Line2 {
	double k, b;

	Line2();
	Line2(double k, double b);
	Line2(const Vec2& dot1, const Vec2& dot2);
	static Line2 fromVectors(const Vec2& dot, const Vec2& vec);

	static Vec2 cross(const Line2 &line1, const Line2 &line2);
};


} //math
} //trek
