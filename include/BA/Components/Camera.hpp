#pragma once

#include "BA/Components/Component.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class Camera : public Component {
public:
	explicit Camera(Entity* owner);

	void useViewFromLayer(IDtype RENDER_LAYER = DEFAULT_RENDER_LAYER);
	void setView(const View& view);
	const View& getView() const;
	void setViewCenter(const Vector2f& center);
private:
	bool m_isUsingCustomView = false;
	ba::IDtype m_layerID = DEFAULT_RENDER_LAYER;
	ba::View m_cameraView;
public:
	static const IDtype CID;
}; // class Camera

} // namespace
