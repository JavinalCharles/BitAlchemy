#pragma once

#include <BA/Window/Window.hpp>

namespace ba {

class Scene {
public:
	virtual void onCreate() = 0;

	virtual void onDestroy() = 0;

	virtual void onActivate();

	virtual void onDeactivate();

	virtual void handleInputs();
	virtual void update(float deltaTime);
	virtual void postUpdate(float deltaTime);
	
	virtual void draw(Window& window) = 0;

private:


}; // class Scene

} // namespace ba