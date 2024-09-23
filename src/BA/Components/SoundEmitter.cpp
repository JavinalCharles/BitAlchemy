#include <BA/Components/SoundEmitter.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/SoundSystem.hpp>

namespace ba {

const IDtype SoundEmitter::CID  = ComponentID::SOUND_EMITTER;

SoundEmitter::SoundEmitter(Entity* owner) :
	Component(owner)
{

}

void SoundEmitter::emitSound(IDtype soundID) {
	Mix_Chunk* chunk = m_owner->CONTEXT->warehouse->getManager<ba::Resources::SoundManager>().at(soundID).get();
	if(chunk == nullptr) {
		throw std::invalid_argument("INVALID! ResourceManager doesn't recognize the sound ID");
	}

	m_sounds.push(soundID);
}

std::queue<IDtype>& SoundEmitter::getSounds(){
	return m_sounds;
}

} // namespace ba
