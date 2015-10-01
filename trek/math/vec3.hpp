#pragma once

#include <iosfwd>

namespace trek {
namespace math {

class Vec3 {
public:
    Vec3(double x = 0, double y = 0, double z = 0);

    Vec3(const double* data);
    Vec3 operator+() const;
    Vec3 operator-() const;
    void operator+= (const Vec3& vec);
    void operator-= (const Vec3& vec);
    Vec3 ort() const;
    double abs() const;

    double& x() { return mData[0]; }
    double& y() { return mData[1]; }
    double& z() { return mData[2]; }

    double x() const { return mData[0]; }
    double y() const { return mData[1]; }
    double z() const { return mData[2]; }

    double* data() { return mData; }
    const double* data() const { return mData; }

    double& operator[](size_t i);
    double  operator[](size_t i) const;

    void rotateX(double ang);
    void rotateY(double ang);
    void rotateZ(double ang);
    void rotate(const Vec3& vec, double ang);

    double* begin();
    double* end();

    const double* begin() const;
    const double* end()   const;

private:
    double mData[3];
};

bool operator==(const Vec3& a, const Vec3& b);
double operator* (const Vec3& a, const Vec3& b);
Vec3 operator& (const Vec3& a, const Vec3& b);

Vec3 operator* (const Vec3& vec, double num);
Vec3 operator/ (const Vec3& vec, double num);

Vec3 operator+ (const Vec3& a, const Vec3& b);
Vec3 operator- (const Vec3& a, const Vec3& b);

double range(const Vec3& a, const Vec3& b);

double angle(const Vec3& a, const Vec3& b);

std::ostream& operator<<(std::ostream& stream, const Vec3& vec);

} //math
} //trek
