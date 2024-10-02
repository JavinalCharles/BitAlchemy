#include "TextScene.hpp"

#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

using namespace ba;
using namespace ba::Resources;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	ba::Engine engine("Text Sample", {0, 0, 968, 605}, SDL_WINDOW_SHOWN);

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	PathFinder::addCommonPath(prefPath);
	// engine.getResourceManager().addToSearchPaths(prefPath);

	engine.init();
	engine.setFPSLimit(23);

	auto textScene = engine.createScene<ba::TextScene>();
	engine.getSceneManager().switchToScene(textScene.first);

	engine.run();

	engine.cleanUp();

	return 0;
}
