#pragma once
#include <BA/Types.hpp>


namespace ba {


/**
 * class ba::Entity
 * - Represents a general-purpose object
 * 
*/

class Entity {
public: // Attributes
	static IDtype entityCreated;

	const IDtype ID;

public: // Methods
	Entity();

	void awake();
	void start();
	void update(float deltaTime);
	void postUpdate(float deltaTime);
}; // class Entity

} // namespace ba