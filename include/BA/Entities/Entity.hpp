#pragma once

#include <vector>
#include <memory>
#include <BA/Components/Colliders/Collider.hpp>
#include "BA/Components/Component.hpp"
#include "BA/Components/Drawable.hpp"
#include "BA/Entities/SharedContext.hpp"
#include <BA/Entities/Transformable.hpp>

namespace ba {

class Entity : public Transformable {
public: // ATTRIBUTES
	static unsigned count;
	const unsigned ID;

	const ba::SharedContext* CONTEXT;
public: // METHODS & CONSTRUCTORS
	Entity(ba::SharedContext* context);

	/**
	 * awake()
	 * Use to ensure that all components are present and all attributes are initialized.
	*/
	virtual void awake();

	bool isStatic() const;
	void setStatic(bool isStatic);

	bool isQueuedForRemoval() const;
	void queueForRemoval(bool remove = true);

	/**
	 * addComponent()
	 * - Creates a Component of Type T and stores it into this entity's Component array. T must be a subclass of ba::Component. Returns a shared_ptr of the created Component.
	*/
	template<typename T>
	std::shared_ptr<T> addComponent();


	/**
	 * getComponent()
	 * - Searches the Component array for an object of type T and return a smart_ptr to it. Returns nullptr if none exist.
	*/
	template<typename T>
	std::shared_ptr<T> getComponent();

	std::shared_ptr<Drawable> getDrawable() const;
	std::shared_ptr<Collider> getCollider() const;

private: // ATTRIBUTES
	
	/* Boolean attribute to signal the systems if this entity is subject for destruction.	*/
	bool m_queuedForRemoval = false;
	bool m_static = false;
	// TODO: Pointer to Game Context here.

	std::vector<std::shared_ptr<ba::Component>> m_components;

	std::shared_ptr<Drawable> m_drawable = nullptr;
	std::shared_ptr<Collider> m_collider = nullptr;

}; // class Entity

template<typename T>
std::shared_ptr<T> Entity::addComponent() {
	// Prevents this method from continuing if T is not a derivation of ba::Component
	static_assert(std::is_base_of<ba::Component, T>::value, "Error. T must be a derived type of ba::Component. Assertion returned false");

	// Checks m_components for any type T object stored. Returns it if it does.
	std::shared_ptr<T> existingComponent = this->getComponent<T>();
	if(existingComponent != nullptr)
		return existingComponent;

	// T does not exist. Create one and store it into memory.
	std::shared_ptr<T> newComponent = std::make_shared<T>(this);
	m_components.push_back(newComponent);

	// Checks if the object is also a drawable.
	if(std::dynamic_pointer_cast<Drawable>(newComponent)) {
		m_drawable = std::dynamic_pointer_cast<ba::Drawable>(newComponent);
	}
	else if (std::dynamic_pointer_cast<Collider>(newComponent)) {
		m_collider = std::dynamic_pointer_cast<Collider>(newComponent);
	}

	return newComponent;
}

template <typename T>
std::shared_ptr<T> Entity::getComponent() {
	// If the component being queried is a Drawable, then return getDrawable instead.
	// if (std::is_base_of<Drawable, T>::value) {
	// 	return getDrawable();
	// }

	// Otherwise, search the m_components array
	for (auto& existingComponent : m_components)
	{
		if (std::dynamic_pointer_cast<T>(existingComponent))
		{
			return std::dynamic_pointer_cast<T>(existingComponent);
		}
	}

	return nullptr;
}


} // namespace ba