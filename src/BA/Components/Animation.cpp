#include <BA/Components/Animation.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/AnimationSystem.hpp>

namespace ba {

const IDtype Animation::CID = ComponentID::ANIMATION;

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

void Animation::setLoop(IDtype animationID, bool isLoop) {
	if (!m_animationMap.contains(animationID)) {
		return;
	}
	m_animationMap.at(animationID).looped = isLoop;
}

void Animation::setFrame(IDtype animationID, std::size_t frameIndex, const Frame& frame) {
	if (!m_animationMap.contains(animationID)) {
		return;
	}
	if(frameIndex > m_animationMap.at(animationID).frames.size()-1) {
		return;
	}

	m_animationMap.at(animationID).frames.at(frameIndex) = frame;
}

void Animation::addFrame(IDtype animationID, const Frame& frame) {
	if (!m_animationMap.contains(animationID)) {
		return;
	}
	m_animationMap.at(animationID).frames.push_back(frame);
}

void Animation::addFrameAction(IDtype animationID, std::size_t frameIndex, const FrameAction& frameAction) {
	if (!m_animationMap.contains(animationID)) {
		return;
	}
	if (frameIndex > m_animationMap.at(animationID).frames.size()-1) {
		return;
	}
	m_animationMap.at(animationID).frames.at(frameIndex).actions.push_front(frameAction);
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