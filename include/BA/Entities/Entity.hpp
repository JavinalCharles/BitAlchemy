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

/***********************************************************************
 * @brief A concept ensuring C is a subtype of ba::Component.
 *
 * @tparam C A class name that should be subtype of Component.
************************************************************************/
template <typename C>
concept ComponentType = std::is_base_of<ba::Component, C>::value;


/***********************************************************************
 * @brief An object to represent each game entity.
 *
************************************************************************/
class Entity : public Transformable {
public:
	/***********************************************************************
	 * @brief Entity Identification.
	 *
	 * Mostly used as keys for maps or sets kept by Systems and Components.
	************************************************************************/
	const IDtype ID;

	/***********************************************************************
	 * @brief A const pointer that allows access to the game's context.
	 *
	************************************************************************/
	const ba::SharedContext* CONTEXT;
public:
	/***********************************************************************
	 * @brief Entiy constructor.
	 *
	 * @param context sets the public attribute Entity::CONTEXT.
	************************************************************************/
	explicit Entity(SharedContext* context);

	/**
	 * awake()
	 * Use to ensure that all components are present and all attributes are initialized.
	*/

	/***********************************************************************
	 * @brief Use to ensure that all components and their attributes are
	 * properly initialized.
	 *
	************************************************************************/
	virtual void awake();

	/***********************************************************************
	 * @brief Checks if this Entity is a static object.
	 *
	 * @return true if this object is static, otherwise false.
	************************************************************************/
	bool isStatic() const;

	/***********************************************************************
	 * @brief Declares whether this Entity is a static object.
	 *
	 * @param isStatic boolean value.
	 *
	 * Static entities are treated differently by Systems from non-static
	 * entities. Setting an entity as static tells the engine that the state of
	 * this entity are not likely to transform, and thus not included in system
	 * loops for efficiency reasons. Example of game objects that should be
	 * declared statics are. but not limited to, as follows:
	 * background, non-moving tiles, decoration objects like flower, plants,
	 * clutter, paths, etc..
	************************************************************************/
	void setStatic(bool isStatic);

	/***********************************************************************
	 * @brief returns a boolean value that tells if this entity is scheduled
	 * to be removed from the main loop.
	 *
	 * @return true if this object is destined for removal, otherwise false.
	************************************************************************/
	bool isQueuedForRemoval() const;

	/***********************************************************************
	 * @brief Sets wether to remove this object or not.
	 *
	 * @param remove Boolean value. Sets whether to remove this object.
	 *
	 * If given a true value, then the entity manager holding a pointer of
	 * this entity shall instruct all systems to clear references of this entity
	 * before eventually freeing memory assigned to this as well as its
	 * components.
	 * Giving a false value within the same frametime after it was given a true
	 * value should prevent that from happening.
	************************************************************************/
	void queueForRemoval(bool remove = true);

	/***********************************************************************
	 * @brief Creates a ComponentType of type T and stores it in this entity's
	 * component array and returning a shared pointer to it.
	 *
	 * @tparam T The type of Component.
	 * @return a shared pointer to the created Component.
	************************************************************************/
	template<ComponentType T>
	std::shared_ptr<T> addComponent();

	/***********************************************************************
	 * @brief returns a shared pointer to the requested component. Returns
	 * nullptr if the component does not exist.
	 *
	 * @tparam T The type of Component.
	 * @return a shared pointer to the requested component or nullptr.
	************************************************************************/
	template<ComponentType T>
	std::shared_ptr<T> getComponent();

	/***********************************************************************
	 * @brief Returns a pointer to the drawable component of this entity, or
	 *  nullptr if this entity does not have one. Equivalent to
	 * @code
	 * entityObject.getComponent<ba::Drawable>();
	 * @endcode
	 *
	 * @return a pointer to the drawable component, or nullptr.
	************************************************************************/
	std::shared_ptr<Drawable> getDrawable() const;

	/***********************************************************************
	 * @brief Returns to pointer to the collider component of his entity, or
	 * nullptr if this entity does not have one. Equivalent to
	 * @code
	 * entityObject.getComponent<ba::Collider>();
	 * @endcode
	 *
	 * @return a pointer to the collider component, or nullptr.
	************************************************************************/
	std::shared_ptr<Collider> getCollider() const;

private: // ATTRIBUTES

	bool m_queuedForRemoval = false;

	bool m_static = false;

	std::map<IDtype, std::shared_ptr<ba::Component>> m_components;

private:
	static IDtype count;
}; // class Entity

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//// IMPLEMENTATION IMPLEMENTATION IMPLEMENTATION IMPLEMENTATION   ////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

template<ComponentType T>
std::shared_ptr<T> Entity::addComponent() {
	// Prevents this method from continuing if T is not a derivation of ba::Component
	// static_assert(std::is_base_of<ba::Component, T>::value, "Error. T must be a derived type of ba::Component. Assertion returned false");
	// Previous line being commented out in favor of concept

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

template <ComponentType T>
std::shared_ptr<T> Entity::getComponent() {
	if (m_components.contains(T::CID)) {
		return std::dynamic_pointer_cast<T>(m_components.at(T::CID));
	}

	return nullptr;
}

} // namespace ba
