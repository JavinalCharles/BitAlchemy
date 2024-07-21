#include "TextScene.hpp"

#include <BA/Engine.hpp>
#include <BA/Scenes/BitAlchemySplash.hpp>

int main() {
	ba::Engine engine("Text Sample", {0, 0, 968, 605}, SDL_WINDOW_SHOWN);

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	engine.getResourceManager().addToSearchPaths(prefPath);

	engine.init();
	engine.setFPSLimit(23);

	std::shared_ptr<ba::TextScene> textScene = engine.createScene<ba::TextScene>();
	engine.addScene(textScene);

	engine.run();

	engine.cleanUp();

	return 0;
}
