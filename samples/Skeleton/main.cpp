#include "SkeletonEntity.hpp"
#include "SkeletonScene.hpp"

#include <BA/Scenes/BitAlchemySplash.hpp>
#include <BA/Systems/AnimationSystem.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>
#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/SoundSystem.hpp>
#include <BA/Engine.hpp>

using namespace ba;

class SkeletonSample : public ba::Engine {
public:
	SkeletonSample();
	SkeletonSample(const std::string& title, ba::IntRect dimension, std::uint32_t winFlags);

	void init() override;

}; // class SkeletonSample

SkeletonSample::SkeletonSample() :
	Engine::Engine()
{

}

SkeletonSample::SkeletonSample(const std::string& title, ba::IntRect dimension, std::uint32_t winFlags) :
	Engine::Engine(title, dimension, winFlags)
{

}

void SkeletonSample::init() {
	Engine::init();

	std::shared_ptr<BitAlchemySplash> bitAlchemySplash = std::make_shared<BitAlchemySplash>(&m_window, &m_resources, &m_sceneManager);

	std::shared_ptr<SkeletonScene> skeletonScene = std::make_shared<SkeletonScene>(&m_window, &m_resources, &m_sceneManager);

	m_sceneManager.add(bitAlchemySplash);
	IDtype skeletonID = m_sceneManager.add(skeletonScene);

	bitAlchemySplash->setSwitchTo(skeletonID);
}

int main() {
	SkeletonSample engine;
	engine.init();

	engine.run();

	engine.cleanUp();

	return 0;
}