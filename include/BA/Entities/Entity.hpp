#pragma once

#include <vector>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <BA/Components/AI/AI.hpp>
#include <BA/Components/Colliders/Collider.hpp>
#include "BA/Components/Component.hpp"
#include "BA/Components/Drawable.hpp"
#include "BA/Entities/SharedContext.hpp"
#include <BA/Entities/Transformable.hpp>

#include <BA/Tools/DebugHelper.hpp>


namespace ba {

/**
 * @brief A concept ensuring C is a subtype of ba::Component.
 *
 * @tparam C A class name that should be subtype of Component.
**/
template <typename C>
concept ComponentType = std::is_base_of<ba::Component, C>::value;


/**
 * @brief An object to represent each game entity.
 *
**/
class Entity : public Transformable {
public:
	/**
	 * @brief Entity Identification.
	 *
	 * Mostly used as keys for maps or sets kept by Systems and Components.
	**/
	const IDtype ID;

	/**
	 * @brief A const pointer that allows access to the game's context.
	 *
	**/
	const ba::SharedContext* CONTEXT;
public:
	/**
	 * @brief Entiy constructor.
	 *
	 * @param context sets the public attribute Entity::CONTEXT.
	**/
	Entity(const SharedContext* context);

	/**
	 * awake()
	 * Use to ensure that all components are present and all attributes are initialized.
	*/

	/**
	 * @brief Use to ensure that all components and their attributes are
	 * properly initialized.
	 *
	**/
	virtual void awake();

	/**
	 * @brief Checks if this Entity is a static object.
	 *
	 * @return true if this object is static, otherwise false.
	**/
	bool isStatic() const;

	/**
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
	**/
	void setStatic(bool isStatic);

	/**
	 * @brief returns a boolean value that tells if this entity is scheduled
	 * to be removed from the main loop.
	 *
	 * @return true if this object is destined for removal, otherwise false.
	**/
	bool isQueuedForRemoval() const;

	/**
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
	**/
	void queueForRemoval(bool remove = true);

	/**
	 * @brief Creates a ComponentType of type T and stores it in this entity's
	 * component array and returning a shared pointer to it. If a component of
	 * type T already exists, then this method will only return that without
	 * creating a new one.
	 *
	 * @tparam T The type of Component.
	 * @return a shared pointer to the created Component.
	**/
	template<ComponentType T>
	std::shared_ptr<T> addComponent();


	/**
	 * @brief Creates a ComponentType of type T and stores it in this entity's
	 * component array and returning a shared pointer to it. If a component of
	 * type T already exists, then this method will only return that without
	 * creating a new one.
	 *
	 * @tparam T  The type of Component.
	 * @param ... Arguments to be passed to T's constuctor besides owner.
	 * @return a shared pointer to the created Component.
	**/
	template<ComponentType T, typename... Args>
	std::shared_ptr<T> addComponent(Args... args);

	/**
	 * @brief returns a shared pointer to the requested component. Returns
	 * nullptr if the component does not exist.
	 *
	 * @tparam T The type of Component.
	 * @return a shared pointer to the requested component or nullptr.
	**/
	template<ComponentType T>
	std::shared_ptr<T> getComponent();

	/**
	 * @brief Returns a pointer to the drawable component of this entity, or
	 * nullptr if this entity does not have one. If entity has stored multiple
	 * Drawable then this method will return the lastes inserted Drawable.
	 *
	 * @return a pointer to the drawable component, or nullptr.
	**/
	std::shared_ptr<Drawable> getDrawable() const;

	/**
	 * @brief Returns a pointer to the collider component of this entity, or
	 * nullptr if this entity does not have one. If entity has stored multiple
	 * Collider then this method will return the latest inserted Collider.
	 *
	 * @return a pointer to the collider component, or nullptr.
	**/
	std::shared_ptr<Collider> getCollider() const;

	/**
	 * @brief Returns a pointer to the AI component of this entity, or nullptr
	 * if this entity does not have one. If entity has stored multiple AI
	 * components, then this method will return the lastest inserted AI.
	 *
	 * @return a pointer to the AI component, or nullptr.
	**/
	std::shared_ptr<AI> getAI() const;
private: // ATTRIBUTES

	bool m_queuedForRemoval = false;

	bool m_static = false;

	std::shared_ptr<Collider> m_collider = nullptr;
	std::shared_ptr<Drawable> m_drawable = nullptr;
	std::shared_ptr<AI> m_ai = nullptr;

	std::unordered_map<std::type_index, std::shared_ptr<ba::Component>> m_components;

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
	const std::type_index INDEX(typeid(T));
	if(m_components.contains(INDEX)) {
		// If entity already has a component of type T, just return it.
		return std::dynamic_pointer_cast<T>(m_components.at(INDEX));
	}

	// T doesn't already exist. construct and store one.
	m_components.insert_or_assign(INDEX, std::make_shared<T>(this));

	if (std::dynamic_pointer_cast<Collider>(m_components.at(INDEX)) != nullptr) {
		m_collider = std::dynamic_pointer_cast<Collider>(m_components.at(INDEX));
	}
	else if (std::dynamic_pointer_cast<Drawable>(m_components.at(INDEX)) != nullptr) {
		m_drawable = std::dynamic_pointer_cast<Drawable>(m_components.at(INDEX));
	}
	else if (std::dynamic_pointer_cast<AI>(m_components.at(INDEX))) {
		m_ai = std::dynamic_pointer_cast<AI>(m_components.at(INDEX));
	}

	return std::dynamic_pointer_cast<T>(m_components.at(INDEX));
}

template<ComponentType T, typename... Args>
std::shared_ptr<T> Entity::addComponent(Args... args) {
	const std::type_index INDEX(typeid(T));
	if (m_components.contains(INDEX)) {
		// If entity already has a component of type T, just return it
		return std::dynamic_pointer_cast<T>(m_components.at(INDEX));
	}
	// T doesn't already exist. create it.
	m_components.insert_or_assign(INDEX, std::make_shared<T>(this, args...));

	if (std::dynamic_pointer_cast<Collider>(m_components.at(INDEX)) != nullptr) {
		m_collider = std::dynamic_pointer_cast<Collider>(m_components.at(INDEX));
	}
	else if (std::dynamic_pointer_cast<Drawable>(m_components.at(INDEX)) != nullptr) {
		m_drawable = std::dynamic_pointer_cast<Drawable>(m_components.at(INDEX));
	}
	else if (std::dynamic_pointer_cast<AI>(m_components.at(INDEX))) {
		m_ai = std::dynamic_pointer_cast<AI>(m_components.at(INDEX));
	}

	return std::dynamic_pointer_cast<T>(m_components.at(INDEX));
}

template <ComponentType T>
std::shared_ptr<T> Entity::getComponent() {
	const std::type_index INDEX(typeid(T));
	if (m_components.contains(INDEX)) {
		return std::dynamic_pointer_cast<T>(m_components.at(INDEX));
	}

	return nullptr;
}

} // namespace ba
