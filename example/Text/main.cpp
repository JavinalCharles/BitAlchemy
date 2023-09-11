#include "TextScene.hpp"

#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

class TextSample : public ba::Engine {
public:
	TextSample();
	TextSample(const std::string& title, ba::IntRect dimension, std::uint32_t winflags);

	virtual void init() override;
private:

}; // class TextSample

TextSample::TextSample() :
	ba::Engine::Engine()
{

}

TextSample::TextSample(const std::string& title, ba::IntRect dimension, std::uint32_t winFlags) :
	ba::Engine::Engine(title, dimension, winFlags)
{

}

void TextSample::init() {
	ba::Engine::init();

	std::shared_ptr<ba::TextScene> textScene = std::make_shared<ba::TextScene>(&m_window, &m_resources, &m_sceneManager);

	m_sceneManager.add(textScene);
}

int main() {
	TextSample engine("Text Sample", {0, 0, 968, 605}, SDL_WINDOW_SHOWN);

	engine.setFPSLimit(23);
	engine.init();

	engine.run();

	engine.cleanUp();

	return 0;
}
