#include <BA/Scenes/BitAlchemySplash.hpp>
#include <BA/Scenes/SceneManager.hpp>

namespace ba {

BitAlchemySplash::BitAlchemySplash() :
	Scene()
{

}

BitAlchemySplash::BitAlchemySplash(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager) :
	Scene(window, resourceManager, sceneManager)
{

}

void BitAlchemySplash::onCreate() {
	m_splashTexID = m_CONTEXT.resources->loadTexture("Poweredby_BitAlchemy_Splash.png");
	m_splashTexture = m_CONTEXT.resources->getTexture(m_splashTexID);
}

void BitAlchemySplash::onDestroy() {
	// TODO: Free Resources
}

void BitAlchemySplash::update(float deltaTime) {
	m_timeElapsed += deltaTime;
	if (m_timeElapsed >= mk_displayTime) {
		IDtype thisID = m_sceneManager->getCurrentSceneID();
		m_sceneManager->switchTo(this->getSWitchTo());
		m_sceneManager->remove(thisID);
	}
}

void BitAlchemySplash::draw(Window& window) {
	SDL_RenderCopy(window.getRenderer(), m_splashTexture, NULL, NULL);
}


} // namespace ba