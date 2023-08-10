#pragma once

#include "BA/Components/Component.hpp"
#include "BA/Window/View.hpp"

namespace ba {

class Camera : public Component {
public:
	explicit Camera(Entity* owner);

	void setView(const View& view);
	const View& getView() const;
	void setViewCenter(const Vector2f& center);
private:
	ba::View m_cameraView;
public:
	static const IDtype CID;
}; // class Camera

} // namespace
