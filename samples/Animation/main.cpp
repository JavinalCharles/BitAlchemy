#include "SkeletonEntity.hpp"
#include <BA/Systems/AnimationSystem.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>
#include <BA/Systems/MovementSystem.hpp>
#include <BA/Engine.hpp>

int main() {
	ba::Engine engine;
	engine.init();

	ba::SharedContext* context = engine.getContext();

	context->entities->includeSystem<ba::AnimationSystem>();
	context->entities->includeSystem<ba::MovementSystem>();
	context->entities->includeSystem<ba::KeyboardControlSystem>();


	auto skeleton = std::make_shared<SkeletonEntity>(context);
	context->entities->add(skeleton);

	engine.run();

	engine.cleanUp();

	return 0;
}