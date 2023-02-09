#pragma once

#include "BA/Types.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

class Component {
public: // Attributes
	const IDtype ownerID;

public: // Methods
	Component() = delete;
	Component(IDtype entityID);

	virtual void awake();
	virtual void start();
}; // class Component

} // namespace ba