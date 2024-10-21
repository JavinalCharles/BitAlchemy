#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

// #include <iostream>

namespace ba {

MovementSystem::MovementSystem(EntityManager* entityManager) :
	ComponentSystem(entityManager)
{

}

void MovementSystem::update(float deltaTime) {
	for(IDtype ID : m_entityIDs) {
		auto e = getEntity(ID);
		if (e == nullptr) {
			continue;
		}
		auto v = e->getComponent<Velocity>();

		Vector2f displacement = v->get() * deltaTime;
		e->move(displacement);

		// v->resetVelocity();
	}
}

void MovementSystem::postUpdate(float) {

}

void MovementSystem::add(std::shared_ptr<Entity>& entity) {
	auto velocity = entity->getComponent<Velocity>();
	if(velocity != nullptr) {
		this->m_entityIDs.insert(entity->ID);
	}
}


} // namespace ba