#pragma once

#include <BA/Components/Animation.hpp>
#include <BA/Components/KeyboardControl.hpp>
#include <BA/Components/Velocity.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Types.hpp>

#include <iostream>

using ba::Entity;
using ba::Animation;
using ba::SharedContext;

class SkeletonEntity : public Entity {
public:
	SkeletonEntity(SharedContext* context);

	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();

private:
	bool m_resourcesLoaded = false;

	ba::Animation* m_anime = nullptr;
	ba::Velocity* m_velocity = nullptr;

	static ba::IDtype rightID;
	static ba::IDtype leftID;

	static ba::IDtype WALK_TEXTURE;
}; // class SkeletonEntity