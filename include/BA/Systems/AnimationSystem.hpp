#pragma once

#include <BA/Components/Animation.hpp>
#include <BA/Systems/ComponentSystem.hpp>


namespace ba {

class AnimationSystem : public ComponentSystem {
public:
	explicit AnimationSystem(EntityManager* entityManager);

	virtual void update(float deltaTime) override;
	virtual void postUpdate(float deltaTime) override;

	virtual void add(std::shared_ptr<Entity>& entity) override;
private:

}; // class AnimationSystem

}; // namespace ba
