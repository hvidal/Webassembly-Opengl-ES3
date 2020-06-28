#include "Vector3.h"
#include <cmath>

Vector3 Vector3::operator-() const noexcept {
    return Vector3(-mX, -mY, -mZ);    
}

Vector3 Vector3::operator-(const Vector3& v) const noexcept {
    return Vector3(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

Vector3 Vector3::normalized() const {
    double length = this->length();
    return Vector3(mX / length, mY / length, mZ / length);
}

double Vector3::length() const noexcept {
    return sqrt(mX * mX + mY * mY + mZ * mZ);
}

double Vector3::dot(const Vector3& v) const noexcept {
    return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

Vector3 Vector3::cross(const Vector3& v) const noexcept {
    return Vector3 {
        mY * v.mZ - mZ * v.mY,
        mZ * v.mX - mX * v.mZ,
        mX * v.mY - mY * v.mX
    };
}