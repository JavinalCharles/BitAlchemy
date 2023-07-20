#pragma once

#include <BA/Components/Animation.hpp>
#include <BA/Components/KeyboardControl.hpp>
#include <BA/Components/Velocity.hpp>
#include <BA/Components/SoundEmitter.hpp>
#include <BA/Inputs/KeyboardInput.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/AISystem.hpp>
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
 
	static const ba::IDtype rightID;
	static const ba::IDtype leftID;
	static const ba::IDtype idleRightID;
	static const ba::IDtype idleLeftID;

	static ba::IDtype IDLE_TEXTURE;
	static ba::IDtype WALK_TEXTURE;
	static ba::IDtype WALK_SOUND;
}; // class SkeletonEntity