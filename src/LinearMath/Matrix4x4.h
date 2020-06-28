#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include <cassert>
#include <array>
#include "Vector3.h"
#include "../Utils/Log.h"


class Matrix4x4 {

	float mData[16];

public:
	Matrix4x4() noexcept {
		identity();
	}
	template<unsigned int N>
	Matrix4x4(const float (&m)[N]) noexcept {
		static_assert(N == 16, "Matrix4x4 should have 16 slots");
		*this = m;
	}
	Matrix4x4(const Matrix4x4&) = default;
	Matrix4x4(Matrix4x4&&) = default;
	Matrix4x4& operator=(const Matrix4x4&) = default;
	Matrix4x4& operator=(Matrix4x4&&) = default;

	template<unsigned int N>
	Matrix4x4& operator=(const float (&m)[N]) {
		static_assert(N == 16, "Matrix4x4 should have 16 slots");
		mData[0] = m[0]; mData[1] = m[1]; mData[2] = m[2]; mData[3] = m[3];
		mData[4] = m[4]; mData[5] = m[5]; mData[6] = m[6]; mData[7] = m[7];
		mData[8] = m[8]; mData[9] = m[9]; mData[10] = m[10]; mData[11] = m[11];
		mData[12] = m[12]; mData[13] = m[13]; mData[14] = m[14]; mData[15] = m[15];
		return *this;
	}

	const float* raw() const noexcept { return &mData[0]; };
	Matrix4x4& identity() noexcept;
	Matrix4x4& translate(const Vector3& offset) noexcept;
	Matrix4x4& multiplyRight(const Matrix4x4& right) noexcept;
	Matrix4x4& multiplyLeft(const Matrix4x4& left) noexcept;
	Matrix4x4& rotate(float phi, float x, float y, float z) noexcept;
	Matrix4x4& rotate(float sinAngle, float cosAngle, float x, float y, float z) noexcept;
	Matrix4x4& lookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept;
	Matrix4x4& perspective(float fovy, float aspect, float zNear, float zFar) noexcept;
	Matrix4x4& ortho(float left, float right, float bottom, float top, float near, float far) noexcept;

	Vector3 getRow(unsigned int i) const noexcept;
	void setRow(unsigned int index, const Vector3& row);

	Vector3 getOrigin() const noexcept { return Vector3(mData[12], mData[13], mData[14]); }
	void setOrigin(const Vector3& origin);
	virtual void debug() const;
};

//-----------------------------------------------------------------------------

inline Vector3 Matrix4x4::getRow(unsigned int i) const noexcept {
	assert(i >= 0 && i <= 3);
	unsigned int v = 4 * i;
	return Vector3(mData[v], mData[v + 1], mData[v + 2]);
}

#endif

