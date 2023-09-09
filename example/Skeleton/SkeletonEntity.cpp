#include "SkeletonEntity.hpp"
#include <BA/Tools/DebugHelper.hpp>

ba::IDtype SkeletonEntity::IDLE_TEXTURE = 0;
ba::IDtype SkeletonEntity::WALK_TEXTURE = 0;
ba::IDtype SkeletonEntity::WALK_SOUND = 0;
const ba::IDtype SkeletonEntity::rightID = 1;
const ba::IDtype SkeletonEntity::leftID = 2;
const ba::IDtype SkeletonEntity::idleRightID = 3;
const ba::IDtype SkeletonEntity::idleLeftID =4;

SkeletonEntity::SkeletonEntity(SharedContext* context) :
	Entity(context)
{
	if(!m_resourcesLoaded) {
		IDLE_TEXTURE = CONTEXT->resources->loadTexture("Skeleton Idle.png");
		WALK_TEXTURE = CONTEXT->resources->loadTexture("Skeleton_Walk.png");
		WALK_SOUND = CONTEXT->resources->loadSound("Concrete 1.wav");
		m_resourcesLoaded = true;
	}

	this->setPosition({128.f, 128.f});
	// this->setOrigin({22/2.f, 33/2.f});
	this->setScale({2.5f, 2.5f});

	auto sprite = this->addComponent<ba::Sprite>(5u, 32u);
	auto anime = this->addComponent<ba::Animation>();
	auto kc = this->addComponent<ba::KeyboardControl>();
	auto vel = this->addComponent<ba::Velocity>();
	auto se = this->addComponent<ba::SoundEmitter>();
	auto timer = this->addComponent<ba::Timer>();

	vel->setMax({64.f, 64.f});

	m_anime = anime.get();
	m_velocity = vel.get();


	/************************************************
	 * Setting up Animations
	*************************************************/
	const ba::IDtype WalkLeft = leftID;
	const ba::IDtype WalkRight = rightID;
	const ba::IDtype IdleLeft = idleLeftID;
	const ba::IDtype IdleRight = idleRightID;

	int L = 22;
	int T = 0;
	const int W = 22;
	const int H = 33;
	const float time = 1.f / 12.f;
	ba::Sequence walkLeft;
	while(L <= 286) {
		ba::Frame frame{
			WALK_TEXTURE,
			ba::IntRect{L, T, -W, H},
			time,
			{}
		};
		ba::IDtype soundID = WALK_SOUND;
		if(walkLeft.frames.size() == 7 || walkLeft.frames.size() == 12) {
			frame.actions.push_front(std::bind([se, soundID](){
				se->emitSound(soundID);
			}));
		}
		walkLeft.frames.push_back(frame);
		L += W;
	}
	walkLeft.looped = true;
	L = 0;
	ba::Sequence walkRight;
	while(L < 286) {
		ba::Frame frame{
			WALK_TEXTURE,
			ba::IntRect{L, T, W, H},
			time,
			{}
		};
		ba::IDtype soundID = WALK_SOUND;
		if(walkRight.frames.size() == 7 || walkRight.frames.size() == 12) {
			frame.actions.push_front(std::bind([se, soundID](){
				se->emitSound(soundID);
			}));
		}
		walkRight.frames.push_back(frame);
		L += W;
	}
	walkRight.looped = true;

	int idleL = 0;
	const int idleT = 0;
	const int idleW = 24;
	const int idleH = 32;
	const float idleTime = 1.f / 11.f;

	ba::Sequence idleRightSequence;
	while(idleL < 264) {
		ba::Frame frame{
			IDLE_TEXTURE,
			ba::IntRect{idleL, idleT, idleW, idleH},
			idleTime,
			{}
		};
		idleRightSequence.frames.push_back(frame);
		idleL += idleW;
	}
	idleRightSequence.looped = true;

	ba::Sequence idleLeftSequence;
	idleL = 24;
	while(idleL <= 264) {
		ba::Frame frame {
			IDLE_TEXTURE,
			ba::IntRect{idleL, idleT, -idleW, idleH},
			idleTime,
			{}
		};
		idleLeftSequence.frames.push_back(frame);
		idleL += idleW;
	}
	idleLeftSequence.looped = true;

	anime->add(WalkLeft, walkLeft);
	anime->add(WalkRight, walkRight);
	anime->add(IdleRight, idleRightSequence);
	anime->add(IdleLeft, idleLeftSequence);
	anime->set(idleRightID);

	auto ki = this->CONTEXT->inputs->getInput<ba::KeyboardInput>();

	auto setVerticalWalkAnimation = std::bind([anime](){
		switch(anime->getCurrentAnimationID()) {
			case WalkLeft:
			case WalkRight:
				break; // SKIP IF THERE'S ALREADY A WALKANIMATION.
			case IdleLeft:
				anime->set(WalkLeft);
				break;
			case IdleRight:
			default:
				anime->set(WalkRight);
		}
	});

	auto stopMoving = std::bind([anime, vel, ki]() {
		bool hasVelocity = false;
		if (!ki->isKeyActive(SDLK_a) && !ki->isKeyActive(SDLK_d)) {
			vel->setX(0.f);
		}
		else {
			hasVelocity = true;
		}
		if (!ki->isKeyActive(SDLK_w) && !ki->isKeyActive(SDLK_s)) {
			vel->setY(0.f);
		}
		else {
			hasVelocity = true;
		}

		if (hasVelocity) {
			return;
		}

		const ba::IDtype CURR = anime->getCurrentAnimationID();

		if (CURR == WalkLeft) {
			anime->set(IdleLeft);
		}
		else if (CURR == WalkRight) {
			anime->set(IdleRight);
		}
		vel->resetVelocity();
	});

	kc->bindOnKeyActive(SDLK_a, std::bind(&ba::Velocity::moveLeft, vel.get()));
	kc->bindOnKeyActive(SDLK_a, std::bind([anime](){
		anime->set(WalkLeft);
	}));
	kc->bindOnKeyActive(SDLK_d, std::bind(&ba::Velocity::moveRight, vel.get()));
	kc->bindOnKeyActive(SDLK_d, std::bind([anime](){
		anime->set(WalkRight);
	}));
	kc->bindOnKeyActive(SDLK_w, std::bind(&ba::Velocity::moveUp, vel.get()));
	kc->bindOnKeyActive(SDLK_w, setVerticalWalkAnimation);
	kc->bindOnKeyActive(SDLK_s, std::bind(&ba::Velocity::moveDown, vel.get()));
	kc->bindOnKeyActive(SDLK_s, setVerticalWalkAnimation);

	kc->bindOnKeyReleased(SDLK_w, stopMoving);
	kc->bindOnKeyReleased(SDLK_a, stopMoving);
	kc->bindOnKeyReleased(SDLK_s, stopMoving);
	kc->bindOnKeyReleased(SDLK_d, stopMoving);

	kc->bindOnKeyPressed(SDLK_RIGHT, std::bind([this](){
		this->rotate(ba::Angle{15.f});
		ba::debug << "Skeleton angle set to: " << this->getRotation().asDegrees() << std::endl;
	}));

	kc->bindOnKeyPressed(SDLK_LEFT, std::bind([this](){
		this->rotate(ba::Angle{-15.f});
		ba::debug << "Skeleton angle set to: " << this->getRotation().asDegrees() << std::endl;
	}));

	auto setIdleAnimation = std::bind([anime](){
		std::shared_ptr<ba::KeyboardInput> keyboard = anime->getOwner()->CONTEXT->inputs->getInput<ba::KeyboardInput>();

		if(keyboard->isKeyActive(SDLK_w) || keyboard->isKeyActive(SDLK_a) || keyboard->isKeyActive(SDLK_s) || keyboard->isKeyActive(SDLK_d)) {
			return;
		}

		switch(anime->getCurrentAnimationID()) {
			case WalkLeft:
				anime->set(IdleLeft);
				break;
			case WalkRight:
			default:
				anime->set(IdleRight);
				break;
		}
	});

	kc->bindOnKeyReleased(SDLK_w, setIdleAnimation);
	kc->bindOnKeyReleased(SDLK_a, setIdleAnimation);
	kc->bindOnKeyReleased(SDLK_s, setIdleAnimation);
	kc->bindOnKeyReleased(SDLK_d, setIdleAnimation);

	// TEST OUT TIMER
	timer->setTimer(std::bind([this](){
		this->setPosition({64.f, 64.f});
	}), 8.f, true);

}


void SkeletonEntity::moveUp() {
	m_velocity->moveUp();
}

void SkeletonEntity::moveLeft() {
	m_anime->set(leftID);
	m_velocity->moveLeft();
}

void SkeletonEntity::moveRight() {
	m_anime->set(rightID);
	m_velocity->moveRight();
}

void SkeletonEntity::moveDown() {
	m_velocity->moveDown();
}
