#include "BA/Components/Camera.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

const IDtype Camera::CID = ba::ComponentID::CAMERA;

Camera::Camera(Entity* owner) :
	Component::Component(owner)
{

}

void Camera::useViewFromLayer(IDtype RENDER_LAYER) {
	m_layerID = RENDER_LAYER;
	m_isUsingCustomView = false;
}

void Camera::setView(const View& view) {
	m_cameraView = view;
	m_isUsingCustomView = true;
}
const View& Camera::getView() const {
	if (m_isUsingCustomView) {
		return m_cameraView;
	}
	return m_owner->CONTEXT->window->getLayerView(m_layerID);
}
void Camera::setViewCenter(const Vector2f& center) {
	const View& view = getView();
	view.setCenter(center);
}


} // namespace ba