#pragma once

#include <BA/Types.hpp>

namespace ba {

/**
 * @brief Forward Declaration. Every non-virtual subclass of ba::Component
 * should nclude <BA/Entities/Entity.hpp> within their header file or thier
 * respective implentation/source file.
**/
class Entity;


/**
 * @brief @brief class interface for all Components owned by an Entity.
 *
 * Components shall store attributes and data related to their respective
 * owner Entity. It shall also be the main means by which anything can change
 * the state of the entity. Besides a few exceptions, Components should only
 * hold data and methods that alter and/or accesses those data. The library
 * should provide many different components for most common usage, but if a user
 * needed to create a custom cumponent that could interact with the systems of
 * this library, then a class needs to be defined to inherit from this
 * interface.
 *
 * Note: An Entity could only have one component of each component type.
 *
 * Note: Defining CID is no longer necessary when inheriting this interface.
**/
class Component {
public:
	/**
	 * @brief Component Constructor
	 * @param owner pointer to the owning Entity of this new Component.
	 *
	 * Note that directly using this constructor (or the constructor of subtype
	 * of Component) isn't necessary except for particular uses. Entity already
	 * already has a means of instantiating its own components. You only need
	 * to call Entity::addComponent<>() function.
	 * @code
	 * std::shared_ptr<Entity> e = std::make_shared<Entity>(...):
	 * e->addComponent<Sprite>();
	 * e->addComponent<Animation>();
	 * e->addComponent<BoxCollider>();
	 * @endcode
	**/
	explicit Component(Entity* owner);

	/**
	 * @brief Component Destructor
	 *
	**/
	virtual ~Component();

	/**
	 * @brief Called once after the entity owner is added to the main loop.
	 *
	 * This awake() does nothing, but subtypes should override this to ensure
	 * data is instantiated properly and the owner entity has the prerequisites
	 * needed to use that component. i.e. Animation component needed Sprite
	 * component to work.
	**/
	virtual void awake();

	/**
	 * @brief Provides a pointer Reference to owner entity.
	 *
	**/
	virtual Entity* getOwner() const;

protected:
	Entity* m_owner;
}; // class Component

} // namespace ba
