#pragma once

#include <BA/Systems/ComponentSystem.hpp>

namespace ba {

class SoundSystem : public ComponentSystem {
public:
	SoundSystem(EntityManager* entityManager);

	virtual void postUpdate(float deltaTime) override;

	virtual void add(std::shared_ptr<Entity>& entity) override;
private:

}; // class SoundSystem

} // namespace ba