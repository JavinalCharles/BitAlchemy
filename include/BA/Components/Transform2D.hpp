#pragma once

#include "BA/Components/Component.hpp"
#include "BA/Systems/Vector2.hpp"
#include "BA/Systems/Rect.hpp"

namespace ba {

class Transform2D : public Component {
public:
	Transform2D(float x = 0.f, float y = 0.f, float scaleX = 1.f, float scaleY = 1.f, float rotation = 0.f);
	Transform2D(Vector2f position, Vector2f scale, float rotation);

	Transform2D& translate(float x, float y);
	Transform2D& translate(Vector2f direction);
	Transform2D& scale(float scaleX, float scaleY);
	Transform2D& scale(Vector2f magnitude);
	Transform2D& rotate(float angle);
	Transform2D& setRotation(float angle);

	Vector2f getPosition() const;
	Vector2f getScale() const;
	float getRotation() const;
private:
	Vector2f position;
	Vector2f magnitude;
	float angle;
}; // class Transform

} // namespace ba