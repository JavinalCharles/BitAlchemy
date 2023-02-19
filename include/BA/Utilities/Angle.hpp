#pragma once

#include <cassert>

namespace ba {

class Angle {
public:
	constexpr Angle();

	constexpr explicit Angle(float degres);

	constexpr float asDegrees() const;

	constexpr float asRadians() const;

	constexpr Angle wrapSigned() const;

	constexpr Angle wrapUnsigned() const;

	static const Angle Zero;

private:
	friend constexpr Angle degrees(float angle);
	friend constexpr Angle radians(float angle);

	float m_degrees{}; 

}; // class Angle

constexpr Angle degrees(float angle);

constexpr Angle radians(float angle);

constexpr bool operator==(Angle left, Angle right);

constexpr bool operator!=(Angle left, Angle right);

constexpr bool operator<(Angle left, Angle right);

constexpr bool operator>(Angle left, Angle right);

constexpr bool operator<=(Angle left, Angle right);

constexpr bool operator>=(Angle left, Angle right);

constexpr Angle operator-(Angle right);

constexpr Angle operator+(Angle left, Angle right);

constexpr Angle& operator+=(Angle& left, Angle right);

constexpr Angle operator-(Angle left, Angle right);

constexpr Angle& operator-=(Angle& left, Angle right);

constexpr Angle operator*(Angle left, Angle right);

constexpr Angle& operator*=(Angle& left, Angle right);

constexpr Angle operator/(Angle left, Angle right);

constexpr Angle operator/(Angle left, float right);

constexpr Angle& operator/=(Angle& left, float right);

constexpr Angle operator%(Angle left, Angle right);

constexpr Angle& operator%=(Angle left, Angle right);

#include <BA/Utilities/Angle.inl>

} // namespace ba