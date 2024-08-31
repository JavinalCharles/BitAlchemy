#include "SkeletonEntity.hpp"
#include "SkeletonScene.hpp"

#include <BA/Scenes/BitAlchemySplash.hpp>
#include <BA/Systems/AnimationSystem.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>
#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/SoundSystem.hpp>
#include <BA/Engine.hpp>

using namespace ba;

int main(int argc, char* argv[]) {
	ba::Engine engine;

	fs::path prefPath(SDL_GetPrefPath("bit-alchemy", "assets"));
	engine.getResourceManager().addToSearchPaths(prefPath);

	engine.init();
	engine.setFPSLimit(30u);

	std::shared_ptr<BitAlchemySplash> splashScene = engine.createScene<BitAlchemySplash>();
	std::shared_ptr<SkeletonScene> skeletonScene = engine.createScene<SkeletonScene>();

	engine.addScene(splashScene);
	IDtype skID = engine.addScene(skeletonScene);

	splashScene->setSwitchTo(skID); // Scene will switch to Skeleton Scene after
									// After splash is over.



	engine.run();

	engine.cleanUp();

	return 0;
}
