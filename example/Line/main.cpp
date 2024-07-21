#include "LineScene.hpp"

#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

int main() {
	ba::Engine engine("Line Sample", {0, 0, 512, 512}, SDL_WINDOW_SHOWN);

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	engine.getResourceManager().addToSearchPaths(prefPath);

	engine.init();

	engine.setFPSLimit(23);

	std::shared_ptr<ba::LineScene> lineScne = engine.createScene<ba::LineScene>();
	engine.addScene(lineScne);

	engine.run();

	engine.cleanUp();

	return 0;
}
