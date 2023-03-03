#pragma once

namespace ba {

/* Forward Declaration. Every non-virtual subclass of ba::Component should be declared in a file that imports "feather/entities/entity.h"*/
class Entity;

class Component {
public: // METHODS & CONSTRUCTORS
	Component(ba::Entity* owner);
	virtual ~Component();

	virtual void awake();

	virtual ba::Entity* getOwner() const;
protected: // ATTRIBUTES
	ba::Entity* m_owner;

}; // class Component

} // namespace ba