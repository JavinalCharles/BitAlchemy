#include <BA/Generator/TileMapGenerator.hpp>
#include <BA/ResourceManager.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

#include <iostream>
#include <string>

#include "TestMapScene.hpp"

using namespace ba;

class TestMap : public Engine {
public:
	TestMap();

	TestMap(const std::string& title, IntRect dimension, std::uint32_t winFlags);

	void init() override;
};

TestMap::TestMap() :
	Engine::Engine()
{

}

TestMap::TestMap(const std::string& title, IntRect dimension, std::uint32_t winFlags) :
	Engine::Engine(title, dimension, winFlags)
{
}

void TestMap::init() {
	Engine::init();

	std::shared_ptr<BitAlchemySplash> bitAlchemySplash = std::make_shared<BitAlchemySplash>(&m_window, &m_resources, &m_sceneManager);

	std::shared_ptr<TestMapScene> testMapScene = std::make_shared<TestMapScene>(&m_window, &m_resources, &m_sceneManager);

	m_sceneManager.add(bitAlchemySplash);
	IDtype testMapSceneID = m_sceneManager.add(testMapScene);

	bitAlchemySplash->setSwitchTo(testMapSceneID);
}


int main() {
	TestMap engine;
	engine.init();

	engine.run();

	engine.cleanUp();

	return 0;
}
