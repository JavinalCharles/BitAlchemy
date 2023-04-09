#pragma once

#include <queue>
#include <stdexcept>
#include <BA/Components/Component.hpp>
#include <BA/Types.hpp>

namespace ba {

class SoundEmitter : public Component {
	friend class SoundSystem;
public:
	SoundEmitter(Entity* owner);
	
	void emitSound(IDtype soundID);
	
private:
	std::queue<IDtype>& getSounds();

	std::queue<IDtype>	m_sounds;
}; // class SoundEmitter

} // namespace ba