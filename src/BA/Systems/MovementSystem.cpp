#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

namespace ba {

MovementSystem::MovementSystem(EntityManager* entityManager) :
	ComponentSystem(entityManager)
{

}

void MovementSystem::update(float deltaTime) {
	for(const unsigned& ID : m_entityIDs) {
		auto e = m_entities->at(ID);
		auto v = e->getComponent<Velocity>();

		Vector2f displacement = v->get() * deltaTime;
		e->move(displacement);
	}
}

void MovementSystem::postUpdate(float deltaTime) {
	for(const unsigned& ID : m_entityIDs) {
		auto v = m_entities->at(ID)->getComponent<Velocity>();
		v->resetVelocity();
	}

}

void MovementSystem::add(std::shared_ptr<Entity>& entity) {
	auto velocity = entity->getComponent<Velocity>();
	if(velocity != nullptr) {
		this->m_entityIDs.insert(entity->ID);
	}
}


} // namespace ba