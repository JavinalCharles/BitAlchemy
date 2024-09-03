#include <BA/Generator/TileMapGenerator.hpp>
#include <BA/ResourceManager.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

#include <iostream>
#include <string>

#include "TestMapScene.hpp"

using namespace ba;

int main() {
	ba::Engine engine;

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	engine.getResourceManager().addToSearchPaths(prefPath);
	engine.setWindowDimension(IntRect(0, 0, 780, 648));

	engine.init();

	std::shared_ptr<BitAlchemySplash> splashScene = engine.createScene<BitAlchemySplash>();
	std::shared_ptr<TestMapScene> mapScene = engine.createScene<TestMapScene>();
	engine.addScene(splashScene);
	IDtype mapSceneID = engine.addScene(mapScene);

	splashScene->setSwitchTo(mapSceneID);

	engine.run();

	engine.cleanUp();

	return 0;
}
