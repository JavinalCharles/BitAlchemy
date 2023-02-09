#include "BA/Components/Transform2D.hpp"

namespace ba {

Transform2D::Transform2D(float x, float y, float scaleX, float scaleY, float rotation) 
	: position(x, y),
	magnitude(scaleX, scaleY),
	angle(rotation)
{

}

Transform2D::Transform2D(Vector2f position, Vector2f scale, float angle)
	: position(position),
	magnitude(scale),
	angle(rotation)
{

}

Transform2D& Transform2D::translate(float x, float y) {
	position.x += x;
	position.y += y;
	return *this;
}

Transform2D& Transform2D::translate(Vector2f direction) {
	position += direction;
	return *this;
}

Transform2D& Transform2D::scale(float scaleX, float scaleY) {
	magnitude.x *= scaleX;
	magnitude.y *= scaleY;
	return *this;
}

Transform2D& Transform2D::scale(Vector2f magnitude) {
	this->magnitude *= magnitude;
	return *this;
}

Transform2D& Transform2D::rotate(float angle) {
	this->angle += angle;
	return *this;
}

Transform2D& Transform::setRotation(float angle) {
	this->angle = angle;
	return *this;
}

Vector2f Transform2D::getPosition() const {
	return position;
}

Vector2f Transform2D::getScale() const {
	return magnitude;
}

float Transform2D::getRotation() const {
	return angle;
}


} // namespace ba