#include "BA/Systems/TimerSystem.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Components/Timer.hpp"
#include "BA/Systems/ComponentSystem.hpp"

namespace ba {

TimerSystem::TimerSystem(EntityManager* entityManager) :
	ComponentSystem::ComponentSystem(entityManager)
{

}

void TimerSystem::update(float deltaTime) {
	for(auto& ID: this->getIDs()) {
		auto e = getEntity(ID);
		if (e == nullptr) {
			continue;
		}
		auto t = e->getComponent<Timer>();
		auto& m = t->getTimedActions();

		auto i = m.begin();
		while (i != m.end()) {	
			if (i->second.elapsedTime >= i->second.timeToActivate) {
				i->second.action();
				if(i->second.isLoop) {
					i->second.elapsedTime = 0.f + deltaTime;
					++i;
				}
				else {
					i = m.erase(i);
				}
			}
			else {
				i->second.elapsedTime += deltaTime;
				++i;
			}
		}
	}
}

void TimerSystem::add(std::shared_ptr<Entity>& entity) {
	if (entity->getComponent<Timer>() != nullptr) {
		this->addID(entity->ID);
	}
}

} // namespace ba