#include "BA/Components/Component.hpp"

namespace ba {

Component::Component(ba::Entity* owner)
	: m_owner(owner) 
{

}

Component::~Component() {

}

void Component::awake() {

}

ba::Entity* Component::getOwner() const {
	return m_owner;
}

} // namespace ba