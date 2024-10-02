#pragma once

#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <BA/Entities/Entity.hpp>
#include <BA/Scenes/Scene.hpp>
#include <BA/Types.hpp>

namespace ba {

class BitAlchemySplash : public Scene {
public:
	BitAlchemySplash();
	BitAlchemySplash(Window* window, ba::Resources::Warehouse* warehouse, SceneManager* sceneManager);

	virtual void onCreate();

	virtual void onDestroy();

	virtual void update(float deltaTime) override;

	virtual void draw(Window& window);

	void setSwitchToScene(std::type_index index);

private:
	IDtype			m_splashTexID		= 0;
	SDL_Texture*	m_splashTexture 	= nullptr;
	float			m_timeElapsed 		= 0.0f;
	const float		mk_displayTime 		= 3.75f;

	std::type_index m_switchToIndex = typeid(int);

}; // class BitAlchemySplash

} // namepapce ba