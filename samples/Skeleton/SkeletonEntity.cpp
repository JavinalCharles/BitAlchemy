#include "SkeletonEntity.hpp"

ba::IDtype SkeletonEntity::WALK_TEXTURE = 0;
ba::IDtype SkeletonEntity::rightID = 1;
ba::IDtype SkeletonEntity::leftID = 2;

SkeletonEntity::SkeletonEntity(SharedContext* context) :
	Entity(context)
{
	if(!m_resourcesLoaded) {
		WALK_TEXTURE = CONTEXT->resources->loadTexture("Skeleton_Walk.png");
		m_resourcesLoaded = true;

	}

	this->setPosition({128.f, 128.f});
	// this->setOrigin({22/2.f, 33/2.f});
	this->setScale({2.5f, 2.5f});

	auto sprite = this->addComponent<ba::Sprite>();
	auto anime = this->addComponent<ba::Animation>();
	auto kc = this->addComponent<ba::KeyboardControl>();
	auto vel = this->addComponent<ba::Velocity>();

	vel->setMax({64.f, 64.f});

	m_anime = anime.get();
	m_velocity = vel.get();

	/************************************************
	 * Setting up Animations
	*************************************************/
	const ba::IDtype WalkLeft = leftID;
	const ba::IDtype WalkRight = rightID;
	int L = 22;
	int T = 0;
	const int W = 22;
	const int H = 33;
	const float time = 1.f / 12.f;
	ba::Sequence walkLeft;
	while(L <= 286) {
		walkLeft.frames.push_back(ba::Frame{
			WALK_TEXTURE,
			ba::IntRect{L, T, -W, H},
			time
		});
		L += W;
	}
	walkLeft.looped = true;
	L = 0;
	ba::Sequence walkRight;
	while(L < 286) {
		walkRight.frames.push_back(ba::Frame{
			WALK_TEXTURE,
			ba::IntRect{L, T, W, H},
			time
		});
		L += W;
	}
	walkRight.looped = true;

	anime->add(WalkLeft, walkLeft);
	anime->add(WalkRight, walkRight);
	anime->set(WalkRight);

	kc->bindOnKeyActive(SDLK_a, std::bind(&ba::Velocity::moveLeft, vel.get()));
	kc->bindOnKeyActive(SDLK_a, std::bind([anime, WalkLeft](){
		anime->set(WalkLeft);
	}));
	kc->bindOnKeyActive(SDLK_d, std::bind(&ba::Velocity::moveRight, vel.get()));
	kc->bindOnKeyActive(SDLK_d, std::bind([anime, WalkRight](){
		anime->set(WalkRight);
	}));
	kc->bindOnKeyActive(SDLK_w, std::bind(&ba::Velocity::moveUp, vel.get()));
	kc->bindOnKeyActive(SDLK_s, std::bind(&ba::Velocity::moveDown, vel.get()));

	kc->bindOnKeyPressed(SDLK_RIGHT, std::bind([this](){
		this->rotate(ba::Angle{15.f});
	}));

	kc->bindOnKeyPressed(SDLK_LEFT, std::bind([this](){
		this->rotate(ba::Angle{-15.f});
	}));
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