#pragma once

#include <BA/Utilities/Rect.hpp>
#include <BA/Utilities/Vector2.hpp>

namespace ba {

class Angle;

/**
 * @brief Define a 3x3 transform matrix 
*/
class Transform {
public:
	/**
	 * @brief Default Constructor
	 * 
	*/
	constexpr Transform();

	/**
	 * @brief Construct a transform from a 3x3 matrix
	*/
	constexpr Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);

	constexpr const float* getMatrix() const;
	constexpr Transform getInverse() const;

	constexpr Vector2f transformPoint(const Vector2f& point) const;
	FloatRect transformRect(const FloatRect& rectangle) const;

	constexpr Transform& combine(const Transform& transform);
	constexpr Transform& translate(const Vector2f& offset);
	Transform& rotate(Angle angle);
	Transform& rotate(Angle angle, const Vector2f& center);

	constexpr Transform& scale(const Vector2f& factors);

	constexpr Transform& scale(const Vector2f& factors, const Vector2f& center);

	static const Transform Identity;
private:
	float m_matrix[16]
	{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}; // class Transform

constexpr Transform operator*(const Transform& left, const Transform& right);

constexpr Transform& operator*=(Transform& left, const Transform& right);
constexpr Vector2f operator*(const Transform& left, const Vector2f& right);
constexpr bool operator==(const Transform& left, const Transform& right);
constexpr bool operator!=(const Transform& left, const Transform& right);

#include <BA/Utilities/Transform.inl>
} // namespace ba