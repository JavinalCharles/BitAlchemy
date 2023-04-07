#include <BA/Components/Animation.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/AnimationSystem.hpp>

namespace ba {

Animation::Animation(Entity* owner) :
	Component(owner) 
{

}

void Animation::awake() {
	auto sprite = m_owner->getComponent<Sprite>();
	if(sprite == nullptr)
		throw std::runtime_error("Sprite component required alongside Animation component.");
	m_sprite = sprite.get();


	this->set(m_currentAnimation);
}

void Animation::add(IDtype animationID, Sequence sequence) {
	m_animationMap.insert_or_assign(animationID, sequence);

	if (m_sprite != nullptr && !m_sprite->hasTexture()) {
		set(animationID);
	}
}

void Animation::set(IDtype animationID) {
	if (!m_animationMap.contains(animationID)) {
		throw std::invalid_argument("INVALID! No matching animation ID found.");
	}
	if(animationID == m_currentAnimation)
		return;

	m_currentAnimation = animationID;
	
	if(m_sprite != nullptr) {
		Frame& F = m_animationMap.at(m_currentAnimation).frames[0];
		m_sprite->setTexture(F.textureID, F.textureRect);
	}
	m_currentFrame = 0;
	m_currentFrameTime = 0.f;
}

IDtype Animation::getCurrentAnimationID() const {
	return m_currentAnimation;
}

const Sequence& Animation::getCurrentSequence() const {
	return m_animationMap.at(m_currentAnimation);
}

} // namespace ba