#include "SkeletonEntity.hpp"
#include "SkeletonScene.hpp"

#include <BA/Scenes/BitAlchemySplash.hpp>
#include <BA/Systems/AnimationSystem.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>
#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/SoundSystem.hpp>
#include <BA/Engine.hpp>

using namespace ba;
using namespace ba::Resources;

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	ba::Engine engine;

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	PathFinder::addCommonPath(prefPath);
	// engine.getResourceManager().addToSearchPaths(prefPath);

	engine.init();
	engine.setFPSLimit(60u);

	auto splashScene = engine.createScene<BitAlchemySplash>();
	auto skeletonScene = engine.createScene<SkeletonScene>();

	splashScene.second->setSwitchToScene(skeletonScene.first);
	engine.getSceneManager().switchToScene(splashScene.first);

	engine.run();

	engine.cleanUp();

	return 0;
}
