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

    double& x();
    double& y();
    double& z();

    double x() const;
    double y() const;
    double z() const;

    double* data();
    const double* data() const;

    double& operator[](unsigned int i);
    double  operator[](unsigned int i) const;

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
