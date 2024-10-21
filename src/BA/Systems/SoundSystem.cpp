#include <BA/Systems/SoundSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

namespace ba {

using ba::Resources::SoundManager;

SoundSystem::SoundSystem(EntityManager* entities) :
	ComponentSystem(entities)
{

}

void SoundSystem::postUpdate(float) {
	for(IDtype ID : m_entityIDs) {
		auto e = getEntity(ID);
		if (e == nullptr) {
			continue;
		}
		std::queue<IDtype>& soundQueue = e->getComponent<SoundEmitter>()->getSounds();

		while(!soundQueue.empty()) {
			Mix_Chunk* sound = m_entities->at(ID)->CONTEXT->warehouse->getManager<SoundManager>().at(soundQueue.front()).get();
			Mix_PlayChannel(-1, sound, 0);
			soundQueue.pop();
		}
	}
}

void SoundSystem::add(std::shared_ptr<Entity>& entity) {
	auto soundEmitter = entity->getComponent<SoundEmitter>();
	if(soundEmitter == nullptr) {
		return;
	}
	m_entityIDs.insert(entity->ID);
}

} // namespace ba