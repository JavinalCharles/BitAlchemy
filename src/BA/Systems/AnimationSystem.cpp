#include <BA/Systems/AnimationSystem.hpp>
#include <BA/Components/Animation.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/EntityManager.hpp>

namespace ba {

AnimationSystem::AnimationSystem(EntityManager* entityManager) :
	ComponentSystem(entityManager)
{

}

void AnimationSystem::update(float) {
	
}

void AnimationSystem::postUpdate(float deltaTime) {
	for (IDtype ID : m_entityIDs) {
		auto a = m_entities->at(ID)->getComponent<Animation>();

		const Sequence& s = a->getCurrentSequence();

		if((s.frames.size() > 1) && (s.looped || a->m_currentFrame < s.frames.size() - 1)) {
			a->m_currentFrameTime += deltaTime;

			if(a->m_currentFrameTime >= s.frames[a->m_currentFrame].displaySeconds) {
				a->m_currentFrameTime = 0.f;

				a->m_currentFrame = ((a->m_currentFrame + 1) % s.frames.size());
				a->m_sprite->setTexture(s.frames[a->m_currentFrame].textureID);
				a->m_sprite->setTextureRect(s.frames[a->m_currentFrame].textureRect);
			}
			
		}
	}
}

void AnimationSystem::add(std::shared_ptr<Entity>& entity) {
	auto a = entity->getComponent<Animation>();

	if (a != nullptr) {
		m_entityIDs.insert(entity->ID);
	}

}

} // namespace ba