#pragma once

#include <functional>

#include <BA/Components/AI/ProgrammedAI.hpp>
#include <BA/Components/Animation.hpp>
#include <BA/Components/Sprite.hpp>
#include <BA/Components/Velocity.hpp>
#include <BA/Components/Timer.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Types.hpp>


using ba::Entity;
using ba::Animation;
using ba::Velocity;
using ba::SharedContext;
using ba::IDtype;

class BlueCharEntity : public Entity {
public:
	BlueCharEntity(SharedContext* context);

	IDtype getDirection() const;
	void setDirection(IDtype direction);
private:
	bool m_resourcesLoaded = false;

	Animation* m_anime = nullptr;
	Velocity* m_velocity = nullptr;

	IDtype m_direction;

	static const IDtype east;
	static const IDtype south;
	static const IDtype west;
	static const IDtype north;

	static const IDtype rightID;
	static const IDtype leftID;
	static const IDtype idleID;

	static IDtype CHAR_TEXTURE;

}; // class BlueCharEntity 
