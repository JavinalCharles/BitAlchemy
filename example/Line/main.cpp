#include "LineScene.hpp"

#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

class LineSample : public ba::Engine {
public:
	LineSample();
	LineSample(const std::string& title, ba::IntRect dimension, std::uint32_t winflags);

	virtual void init() override;
}; // class LineSample

LineSample::LineSample() :
	ba::Engine::Engine()
{

}

LineSample::LineSample(const std::string& title, ba::IntRect dimension, std::uint32_t winFlags) :
	ba::Engine::Engine(title, dimension, winFlags)
{

}

void LineSample::init() {
	Engine::init();

	std::shared_ptr<ba::LineScene> lineScene = std::make_shared<ba::LineScene>(&m_window, &m_resources, &m_sceneManager);

	m_sceneManager.add(lineScene);
}

int main() {
	LineSample engine("Line Sample", {0, 0, 512, 512}, SDL_WINDOW_SHOWN);

	engine.setFPSLimit(23);
	engine.init();

	engine.run();

	engine.cleanUp();

	return 0;
}
