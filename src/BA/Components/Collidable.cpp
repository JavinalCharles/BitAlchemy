#include "BA/Components/Collidable.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

const IDtype Collidable::CID = ba::ComponentID::COLLIDABLE;

Collidable::Collidable(Entity* owner) :
	Component::Component(owner)
{

}

} // namespace ba