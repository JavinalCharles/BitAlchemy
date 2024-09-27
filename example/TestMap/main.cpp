#include <BA/Generator/TileMapGenerator.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

#include <iostream>
#include <string>

#include "TestMapScene.hpp"

using namespace ba;
namespace fs = std::filesystem;
using namespace ba::Resources;

int main() {
	ba::Engine engine;

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	PathFinder::addCommonPath(prefPath);

	// engine.getResourceManager().addToSearchPaths(prefPath);
	const IntRect WINDOW_DIMENSION(0, 0, 972, 754);
	engine.getWindow().setDimension(WINDOW_DIMENSION);
	// engine.getWindow().setView(ba::View(WINDOW_DIMENSION));
	
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
