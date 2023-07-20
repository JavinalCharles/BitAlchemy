#include "BA/Components/AI/AI.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

const IDtype AI::CID = ComponentID::A_I;

AI::AI(Entity* owner) :
	Component::Component(owner)
{
	
}

void AI::behave(float) {
	
}

} // namespace ba