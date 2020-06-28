#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <stdint.h>

class Vector3 
{
    double mX;
    double mY;
    double mZ;
    double mW;

public:
    Vector3(): mX(0), mY(0), mZ(0), mW(0) {}
    Vector3(double x, double y, double z): mX(x), mY(y), mZ(z), mW(1) {}

    Vector3 operator-() const noexcept;
    Vector3 operator-(const Vector3& v) const noexcept;

    double x() const noexcept { return mX; }
    double y() const noexcept { return mY; }
    double z() const noexcept { return mZ; }
    double w() const noexcept { return mW; }    

    double length() const noexcept;
    double dot(const Vector3&) const noexcept;
    Vector3 normalized() const;
    Vector3 cross(const Vector3& v) const noexcept;
};

//-----------------------------------------------------------------------------

#endif
