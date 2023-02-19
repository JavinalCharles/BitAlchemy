constexpr float PI = 3.141592654F;

constexpr float positiveRemainder(float a, float b) {
	assert(b > 0.0f);

	const float val = a - static_cast<float>(static_cast<int>(a/b)) * b;
	if (val >= 0.f)
		return val;
	else
		return val + b;
}

constexpr Angle::Angle() = default;

constexpr float Angle::asDegrees() const {
	return m_degrees;
}

constexpr float Angle::asRadians() const {
	return m_degrees * (PI / 180);
}

constexpr Angle Angle::wrapSigned() const {
	return degrees(positiveRemainder(m_degrees + 180, 360) - 180);
}

constexpr Angle Angle::wrapUnsigned() const {
	return degrees(positiveRemainder(m_degrees, 360));
}

constexpr Angle::Angle(float degres)
	: m_degrees(degres)
{

}

constexpr Angle degrees(float angle) {
	return Angle(angle);
}

constexpr Angle radians(float angle) {
	return Angle(angle * (180 / PI));
}

constexpr bool operator==(Angle left, Angle right)
{
    return left.asDegrees() == right.asDegrees();
}

constexpr bool operator!=(Angle left, Angle right)
{
    return left.asDegrees() != right.asDegrees();
}

constexpr bool operator<(Angle left, Angle right)
{
    return left.asDegrees() < right.asDegrees();
}

constexpr bool operator>(Angle left, Angle right)
{
    return left.asDegrees() > right.asDegrees();
}

constexpr bool operator<=(Angle left, Angle right)
{
    return left.asDegrees() <= right.asDegrees();
}

constexpr bool operator>=(Angle left, Angle right)
{
    return left.asDegrees() >= right.asDegrees();
}

constexpr Angle operator-(Angle right)
{
    return degrees(-right.asDegrees());
}

constexpr Angle operator+(Angle left, Angle right)
{
    return degrees(left.asDegrees() + right.asDegrees());
}

constexpr Angle& operator+=(Angle& left, Angle right)
{
    return left = left + right;
}

constexpr Angle operator-(Angle left, Angle right)
{
    return degrees(left.asDegrees() - right.asDegrees());
}

constexpr Angle& operator-=(Angle& left, Angle right)
{
    return left = left - right;
}

constexpr Angle operator*(Angle left, float right)
{
    return degrees(left.asDegrees() * right);
}

constexpr Angle operator*(float left, Angle right)
{
    return right * left;
}

constexpr Angle& operator*=(Angle& left, float right)
{
    return left = left * right;
}

constexpr Angle operator/(Angle left, float right)
{
    return degrees(left.asDegrees() / right);
}

constexpr Angle& operator/=(Angle& left, float right)
{
    return left = left / right;
}

constexpr Angle operator/(Angle left, Angle right)
{
    return Angle(left.asDegrees() / right.asDegrees());
}

constexpr Angle operator%(Angle left, Angle right)
{
    return degrees(positiveRemainder(left.asDegrees(), right.asDegrees()));
}

constexpr Angle& operator%=(Angle& left, Angle right)
{
    return left = left % right;
}