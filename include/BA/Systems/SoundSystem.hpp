#pragma once

#include <BA/Components/SoundEmitter.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/ComponentSystem.hpp>

namespace ba {

class SoundSystem : public ComponentSystem {
public:
	explicit SoundSystem(EntityManager* entityManager);

	virtual void postUpdate(float deltaTime) override;

	virtual void add(std::shared_ptr<Entity>& entity) override;
private:

}; // class SoundSystem

} // namespace ba
