#include "BA/Components/FunctionalCollidable.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

FunctionalCollidable::FunctionalCollidable(Entity* owner) :
	Collidable::Collidable(owner)
{

}

void FunctionalCollidable::onCollisionEnter(IDtype other) {
	for (auto& f : m_exeOnCollisionEnter) {
		f(other);
	}
}

void FunctionalCollidable::onCollisionStay(IDtype other) {
	for (auto& f : m_exeOnCollisionStay) {
		f(other);
	}
}

void FunctionalCollidable::onCollisionExit(IDtype other) {
	for (auto& f : m_exeOnCollisionExit) {
		f(other);
	}
}

void FunctionalCollidable::addOnCollisionEnter(const CollidableFunction& function) {
	m_exeOnCollisionEnter.push_back(function);
}

void FunctionalCollidable::addOnCollisionStay(const CollidableFunction& function) {
	m_exeOnCollisionStay.push_back(function);
}

void FunctionalCollidable::addOnCollisionExit(const CollidableFunction& function) {
	m_exeOnCollisionExit.push_back(function);
}

} // namespace ba