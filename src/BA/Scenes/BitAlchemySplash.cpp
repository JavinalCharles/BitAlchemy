#include <BA/Scenes/BitAlchemySplash.hpp>
#include <BA/Scenes/SceneManager.hpp>

namespace ba {

using ba::Resources::Warehouse;

BitAlchemySplash::BitAlchemySplash() :
	Scene()
{

}

BitAlchemySplash::BitAlchemySplash(Window* window, Warehouse* warehouse, SceneManager* sceneManager) :
	Scene(window, warehouse, sceneManager)
{

}

void BitAlchemySplash::onCreate() {
	ba::Resources::TextureManager& TM = m_CONTEXT.warehouse->getManager<ba::Resources::TextureManager>();
	m_splashTexID = TM.create("Poweredby_BitAlchemy_Splash.png");
	m_splashTexture = TM.at(m_splashTexID).get();
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