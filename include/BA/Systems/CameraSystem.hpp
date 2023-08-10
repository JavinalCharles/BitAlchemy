#pragma once

#include "BA/Components/Camera.hpp"
#include "BA/Systems/ComponentSystem.hpp"

namespace ba {

class CameraSystem : public ComponentSystem {
public:
	explicit CameraSystem(EntityManager* entityManager);

	virtual void update(float deltaTime);

	virtual void add(std::shared_ptr<Entity>& entity);
private:

}; // CameraSystem

} // namespace ba
