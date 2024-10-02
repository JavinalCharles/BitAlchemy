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

namespace fs = std::filesystem;

void BitAlchemySplash::onCreate() {
	ba::Resources::TextureManager& TM = m_CONTEXT.warehouse->getManager<ba::Resources::TextureManager>();
	TM.addPath(std::filesystem::path("Textures"));

	std::optional<fs::path> splashTexture = TM.findFile(fs::path("Poweredby_BitAlchemy_Splash.png"));
	if (splashTexture.has_value()) {
		m_splashTexID = TM.create(splashTexture.value().string());
		m_splashTexture = TM.at(m_splashTexID).get();
	}
}

void BitAlchemySplash::onDestroy() {
	// TODO: Free Resources
}

void BitAlchemySplash::update(float deltaTime) {
	m_timeElapsed += deltaTime;
	if (m_timeElapsed >= mk_displayTime) {
		m_sceneManager->switchToScene(m_switchToIndex);
		m_sceneManager->removeScene(std::type_index(typeid(BitAlchemySplash)));
	}
}

void BitAlchemySplash::draw(Window& window) {
	SDL_RenderCopy(window.getRenderer(), m_splashTexture, NULL, NULL);
}

void BitAlchemySplash::setSwitchToScene(std::type_index index) {
	m_switchToIndex = index;
}


} // namespace ba