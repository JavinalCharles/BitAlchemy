#include "BA/Components/AI/AI.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

const IDtype AI::CID = ComponentID::AI;

AI::AI(Entity* owner) :
	Component::Component(owner)
{
	
}

} // namespace ba