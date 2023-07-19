#include "BlueCharEntity.hpp"

using namespace ba;

const IDtype BlueCharEntity::rightID = 1;
const IDtype BlueCharEntity::leftID = 2;
const IDtype BlueCharEntity::idleID = 3;

const IDtype BlueCharEntity::east = 1;
const IDtype BlueCharEntity::south = 2;
const IDtype BlueCharEntity::west = 3;
const IDtype BlueCharEntity::north = 4;

ba::IDtype BlueCharEntity::CHAR_TEXTURE = 0;

BlueCharEntity::BlueCharEntity(SharedContext* context) :
	Entity(context)
{
	if (!m_resourcesLoaded) {
		CHAR_TEXTURE = CONTEXT->resources->loadTexture("oak_woods_v1.0/character/char_blue.png");
		m_resourcesLoaded = true;
	}

	auto sprite = this->addComponent<Sprite>();
	auto anime = this->addComponent<Animation>();
	auto vel = this->addComponent<Velocity>();
	auto ai = this->addComponent<ProgrammedAI>();

	vel-> setMax({64.f, 64.f});

	m_anime = anime.get();
	m_velocity = vel.get();

	/**********************************
	 * SET UP ANIMATION
	***********************************/
	// IDLE ANIMATION
	IntRect frameRect {
		0, 0, 56, 56 
	};
	const float time = 1.f / 8.f;
	Sequence IdleSequence;
	while(frameRect.l < 336) {
		Frame frame {
			CHAR_TEXTURE,
			frameRect,
			time,
			{}
		};
		frameRect.l += 56;
		IdleSequence.frames.push_back(frame);
	}
	IdleSequence.looped = true;

	// WALKRIGHT ANIMATION
	frameRect.l = 0;
	frameRect.t = 112;
	Sequence WalkRightSequence;
	while(frameRect.l < 448) {
		Frame frame {
			CHAR_TEXTURE,
			frameRect,
			time,
			{}
		};
		frameRect.l += 56;
		WalkRightSequence.frames.push_back(frame);
	}
	WalkRightSequence.looped = true;

	// WALKLEFT ANIMATION
	frameRect.l = 56;
	frameRect.w = -56;
	Sequence WalkLeftSequence;
	while(frameRect.l <= 448) {
		Frame frame {
			CHAR_TEXTURE,
			frameRect,
			time,
			{}
		};
		frameRect.l += 56;
		WalkLeftSequence.frames.push_back(frame);
	}
	WalkLeftSequence.looped = true;

	anime->add(idleID, IdleSequence);
	anime->add(rightID, WalkRightSequence);
	anime->add(leftID, WalkLeftSequence);
	anime->set(rightID);

	// START ANIMATION
	this->setPosition({512.f, 512.f});
	m_velocity->moveRight();

	Condition goingRight = std::bind([this](float)-> bool {
		return this->getDirection() == east;
	}, std::placeholders::_1);

	Behavior walkRightUntil = std::bind([vel, this](float){
		if (this->getPosition().x >= 512) {
			this->setDirection(south);
			vel->moveDown();
		}
		else {
			vel->moveRight();
		}
	}, std::placeholders::_1);
	ai->assignBindings(1, goingRight, walkRightUntil);


	Condition goingDown = std::bind([this](float)-> bool {
		return this->getDirection() == south;
	}, std::placeholders::_1);

	IDtype left = leftID;
	Behavior walkDownUntil = std::bind([vel, anime, left, this](float){
		if (this->getPosition().y >= 256) {
			this->setDirection(west);
			vel->moveLeft();
			anime->set(left);
		}
		else {
			vel->moveDown();
		}
	}, std::placeholders::_1);
	ai->assignBindings(2, goingDown, walkDownUntil);

	Condition goingLeft = std::bind([this](float)-> bool {
		return this->getDirection() == west;
	}, std::placeholders::_1);

	Behavior walkLeftUntil = std::bind([vel, this](float){
		if (this->getPosition().x <= 64) {
			this->setDirection(north);
			vel->moveUp();
		}
		else {
			vel->moveLeft();
		}
	}, std::placeholders::_1);
	ai->assignBindings(3, goingLeft, walkLeftUntil);

	Condition goingUp = std::bind([this](float)-> bool {
		return this->getDirection() == north;
	}, std::placeholders::_1);

	IDtype right = rightID;
	Behavior walkUpUntil = std::bind([vel, anime, right, this](float){
		if (this->getPosition().y <= 64) {
			this->setDirection(east);
			vel->moveRight();
			anime->set(right);
		}
		else {
			vel->moveUp();
		}
	}, std::placeholders::_1);
	ai->assignBindings(4, goingUp, walkUpUntil);

	Condition idling = std::bind([vel](float) -> bool {
		return true;
	}, std::placeholders::_1);

	Behavior startWalkingRight = std::bind([vel, anime, right, this](float){
		this->setDirection(east);
		vel->moveRight();
		anime->set(right);
	}, std::placeholders::_1);
	ai->assignBindings(5, idling, startWalkingRight);

}

IDtype BlueCharEntity::getDirection() const {
	return m_direction;
}

void BlueCharEntity::setDirection(IDtype direction) {
	m_direction = direction;
}