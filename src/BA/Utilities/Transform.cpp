#include <BA/Utilities/Transform.hpp>
#include <BA/Utilities/Angle.hpp>

#include <cmath>

namespace ba {

Transform& Transform::rotate(Angle angle) {
	float rad = angle.asRadians();
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	Transform rotation(
		cos, -sin, 0,
		sin,  cos, 0,
		0,    0,   1 
	);

	return combine(rotation);
}

Transform& Transform::rotate(Angle angle, const Vector2f& center) {
	float rad = angle.asRadians();
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	Transform rotation(
		cos, -sin, center.x * (1 - cos) + center.y * sin,
		sin,  cos, center.y * (1 - cos) - center.x * sin,
		0,    0,   1
	);

	return combine(rotation);
}


} // namespace ba