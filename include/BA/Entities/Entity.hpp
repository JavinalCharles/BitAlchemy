#pragma once

#include <iostream>
#include <map>
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
	explicit Entity(SharedContext* context);

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

	std::map<IDtype, std::shared_ptr<ba::Component>> m_components;

	// std::shared_ptr<Drawable> m_drawable = nullptr;
	// std::shared_ptr<Collider> m_collider = nullptr;
}; // class Entity

template<typename T>
std::shared_ptr<T> Entity::addComponent() {
	// Prevents this method from continuing if T is not a derivation of ba::Component
	static_assert(std::is_base_of<ba::Component, T>::value, "Error. T must be a derived type of ba::Component. Assertion returned false");

	if(m_components.contains(T::CID)) {
		if (std::dynamic_pointer_cast<T>(m_components.at(T::CID))) {
			// If T already exists, just return it.
			return std::dynamic_pointer_cast<T>(m_components.at(T::CID));
		}
		else {
			// Otherwise, if T does not exist but a similar CID is used, replaced the object mapped to that CID.
			m_components.at(T::CID) = std::make_shared<T>(this);
		}
	}
	else {
		// T doesn't already exist. create it.
		m_components.insert(std::make_pair(T::CID, std::make_shared<T>(this)));
	}

	return std::dynamic_pointer_cast<T>(m_components.at(T::CID));
}

template <typename T>
std::shared_ptr<T> Entity::getComponent() {
	if (m_components.contains(T::CID)) {
		return std::dynamic_pointer_cast<T>(m_components.at(T::CID));
	}

	return nullptr;
}

} // namespace ba
