#pragma once

#include <array>
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
	constexpr FloatRect transformRect(const FloatRect& rectangle) const;

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


/**
 * BELOW ARE METHODS AND FUNCTIONS
 * IMPLEMENTATIONS FOR CLASS Transform.
**/
constexpr Transform::Transform() = default;

constexpr Transform::Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22) :
	m_matrix
	{
		a00, a10, 0.f, a20,
		a01, a11, 0.f, a21,
		0.f, 0.f, 1.f, 0.f,
		a02, a12, 0.f, a22
	}
{

}

constexpr const float* Transform::getMatrix() const {
	return m_matrix;
}

constexpr Transform Transform::getInverse() const {
    float det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
                m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
                m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

    if (det != 0.f)
    {
        return Transform( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
                         -(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
                          (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
                         -(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
                          (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
                         -(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
                          (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
                         -(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
                          (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
    }
    else
    {
        return Identity;
    }
}

constexpr Vector2f Transform::transformPoint(const Vector2f& point) const {
	return Vector2f(
		m_matrix[0] * point.x + m_matrix[4] * point.y + m_matrix[12],
		m_matrix[1] * point.x + m_matrix[5] * point.y + m_matrix[13]
	);
}

constexpr FloatRect Transform::transformRect(const FloatRect& rect) const {
	Vector2f pos = rect.getPosition();
	const std::array points = {
			transformPoint(pos),
			transformPoint(pos + Vector2f(0.f, rect.h)),
			transformPoint(pos + Vector2f(rect.w, 0.f)),
			transformPoint(pos + rect.getArea())
	};
	Vector2f pmin = points[0];
    Vector2f pmax = points[0];

	for (const Vector2f& p : points) {
		if (p.x < pmin.x) 
			pmin.x = p.x;
		else if (p.x > pmax.x) 
			pmax.x = p.x;

		if (p.y < pmin.y)
			pmin.y = p.y;
		else if (p.y > pmax.y)
			pmax.y = p.y;
	}

	return FloatRect(pmin, pmax - pmin);
}

constexpr Transform& Transform::combine(const Transform& transform) {
	const float* a = m_matrix;
    const float* b = transform.m_matrix;

    // clang-format off
    *this = Transform(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                      a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                      a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                      a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                      a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                      a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                      a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                      a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                      a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);
    // clang-format on

    return *this;
}

constexpr Transform& Transform::translate(const Vector2f& offset)
{
    // clang-format off
    Transform translation(1, 0, offset.x,
                          0, 1, offset.y,
                          0, 0, 1);
    // clang-format on

    return combine(translation);
}

constexpr Transform& Transform::scale(const Vector2f& factors)
{
    // clang-format off
    Transform scaling(factors.x, 0,         0,
                      0,         factors.y, 0,
                      0,         0,         1);
    // clang-format on

    return combine(scaling);
}

constexpr Transform& Transform::scale(const Vector2f& factors, const Vector2f& center)
{
    // clang-format off
    Transform scaling(factors.x, 0,         center.x * (1 - factors.x),
                      0,         factors.y, center.y * (1 - factors.y),
                      0,         0,         1);
    // clang-format on

    return combine(scaling);
}

constexpr Transform operator*(const Transform& left, const Transform& right)
{
    return Transform(left).combine(right);
}

constexpr Transform& operator*=(Transform& left, const Transform& right)
{
    return left.combine(right);
}

constexpr Vector2f operator*(const Transform& left, const Vector2f& right)
{
    return left.transformPoint(right);
}

constexpr bool operator==(const Transform& left, const Transform& right)
{
    const float* a = left.getMatrix();
    const float* b = right.getMatrix();

    // clang-format off
    return ((a[0]  == b[0])  && (a[1]  == b[1])  && (a[3]  == b[3]) &&
            (a[4]  == b[4])  && (a[5]  == b[5])  && (a[7]  == b[7]) &&
            (a[12] == b[12]) && (a[13] == b[13]) && (a[15] == b[15]));
    // clang-format on
}

constexpr bool operator!=(const Transform& left, const Transform& right)
{
    return !(left == right);
}

constexpr Transform Transform::Identity;

} // namespace ba
