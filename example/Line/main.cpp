#include "LineScene.hpp"

#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

using ba::Resources::PathFinder;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	ba::Engine engine("Line Sample", {0, 0, 512, 512}, SDL_WINDOW_SHOWN);

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	PathFinder::addCommonPath(prefPath);

	engine.init();

	engine.setFPSLimit(30);

	auto lineScene = engine.createScene<ba::LineScene>();
	// engine.addScene(lineScne);
	engine.getSceneManager().switchToScene(lineScene.first);

	engine.run();

	engine.cleanUp();

	return 0;
}
