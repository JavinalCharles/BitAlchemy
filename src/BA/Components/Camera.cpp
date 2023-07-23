#include "BA/Components/Camera.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

Camera::Camera(Entity* owner) :
	Component::Component(owner)
{

}

void Camera::setView(const View& view) {
	m_cameraView = view;
}
const View& Camera::getView() const {
	return m_cameraView;
}
void Camera::setViewCenter(const Vector2f& center) {
	m_cameraView.setCenter(center);
}


} // namespace ba