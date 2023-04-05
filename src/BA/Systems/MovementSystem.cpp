#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

#include <iostream>

namespace ba {

MovementSystem::MovementSystem(EntityManager* entityManager) :
	ComponentSystem(entityManager)
{

}

void MovementSystem::update(float deltaTime) {
	for(IDtype ID : m_entityIDs) {
		auto e = m_entities->at(ID);
		auto v = e->getComponent<Velocity>();

		std::clog << "deltaTime: " << deltaTime << "\n"
			<< "Velocity: (" << v->get().x << ", " << v->get().y << ")\n";

		Vector2f displacement = v->get() * deltaTime;
		e->move(displacement);

		std::clog << "Entity #" << ID << " New Position : (" << e->getPosition().x << ", " << e->getPosition().y << ")\n";
		v->resetVelocity();
	}
}

void MovementSystem::postUpdate(float) {

}

void MovementSystem::add(std::shared_ptr<Entity>& entity) {
	auto velocity = entity->getComponent<Velocity>();
	if(velocity != nullptr) {
		std::clog << "Adding Entity #" << entity->ID << " to MovementSystem.\n";

		this->m_entityIDs.insert(entity->ID);
	}
}


} // namespace ba