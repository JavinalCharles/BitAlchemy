#include "TextScene.hpp"

namespace ba {

TextScene::TextScene() :
	Scene::Scene()
{
	m_CONTEXT.entities = &m_entityManager;
}

TextScene::TextScene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager) :
	Scene::Scene(window, resourceManager, sceneManager)
{
	m_CONTEXT.entities = &m_entityManager;
}

void TextScene::handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_MOUSEWHEEL:
				if (event.wheel.y != 0) {
					const ba::View& v = m_CONTEXT.window->getLayerView();
					v.move({0.f, -event.wheel.preciseY * 16.f});
				}
		}
	}
}

void TextScene::onCreate() {

}

void TextScene::onDestroy() {
	m_FPSText.reset();
}

void TextScene::onActivate() {
	std::shared_ptr<Entity> fpsEntity = std::make_shared<Entity>(&m_CONTEXT);
	fpsEntity->setPosition({5.f, 5.f});
	m_FPSText = fpsEntity->addComponent<Text>();
	m_FPSText->loadFontFromFile("UbuntuMono-Bold.ttf", 16);
	m_FPSText->setColor(Color::Blue);

	std::string textStr = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Est pellentesque elit ullamcorper dignissim cras tincidunt lobortis feugiat. Rutrum quisque non tellus orci ac auctor augue mauris. Quam pellentesque nec nam aliquam sem et tortor consequat id. Enim neque volutpat ac tincidunt vitae semper. Non sodales neque sodales ut etiam. Condimentum vitae sapien pellentesque habitant morbi tristique senectus et netus. Elementum tempus egestas sed sed. Magnis dis parturient montes nascetur ridiculus. Facilisis gravida neque convallis a cras semper auctor. Aliquam ultrices sagittis orci a scelerisque. Augue interdum velit euismod in.\n\nHac habitasse platea dictumst quisque. Scelerisque felis imperdiet proin fermentum leo vel. Nisl nisi scelerisque eu ultrices vitae auctor eu augue ut. Vitae auctor eu augue ut lectus. Elit scelerisque mauris pellentesque pulvinar pellentesque habitant morbi tristique. Montes nascetur ridiculus mus mauris vitae. Elementum tempus egestas sed sed. Nec feugiat nisl pretium fusce. Orci porta non pulvinar neque laoreet suspendisse interdum consectetur. Non pulvinar neque laoreet suspendisse interdum consectetur libero. Libero justo laoreet sit amet cursus sit. Blandit cursus risus at ultrices mi tempus imperdiet nulla malesuada. Id ornare arcu odio ut sem. Consectetur lorem donec massa sapien faucibus et molestie ac. Vivamus arcu felis bibendum ut tristique. Scelerisque viverra mauris in aliquam sem. Dui ut ornare lectus sit amet est placerat in egestas. Lectus urna duis convallis convallis tellus id interdum velit. Ut consequat semper viverra nam libero justo laoreet sit amet. Non consectetur a erat nam at.";

	std::shared_ptr<Entity> textEntity = std::make_shared<Entity>(&m_CONTEXT);
	textEntity->setPosition({100.f, 32.f});
	auto textComponent = textEntity->addComponent<Text>();
	textComponent->loadFontFromFile("UbuntuMono-Regular.ttf", 24);
	textComponent->setWrapLength(768);
	textComponent->setColor(Color::White);
	textComponent->setText(textStr);

	m_entityManager.add(fpsEntity);
	m_entityManager.add(textEntity);
}

void TextScene::update(float deltaTime) {
	int fps = static_cast<int>(std::round(1.0f / deltaTime));
	m_FPSText->setText(std::to_string(fps) + " FPS");

	m_entityManager.update(deltaTime);

	m_entityManager.postUpdate(deltaTime);
}

void TextScene::draw(Window& window) {
	m_entityManager.draw(window);
}

} // namespace ba
