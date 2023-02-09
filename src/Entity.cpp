#include "BA/Entities/Entity.hpp"

namespace ba {

IDtype Entity::entityCreated = 0;

Entity::Entity()
	: ID(++Entity::entityCreated) 
{

}


} // namespace ba