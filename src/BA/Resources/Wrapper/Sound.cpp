#include <BA/Resources/Wrapper/Sound.hpp>

namespace ba {
namespace Resources {

Sound::Sound() = default;

Sound::Sound(const std::string& file) {
	loadSound(file);
}

Sound::Sound(const Sound& other) :
	m_sound(other.m_sound),
	m_refCount(other.m_refCount)
{
	if (m_refCount != nullptr) {
		(*m_refCount)++;
	}
}

Sound::Sound(Sound&& other) :
	m_sound(other.m_sound),
	m_refCount(other.m_refCount)
{
	other.m_sound = nullptr;
	other.m_refCount = nullptr;
}

Sound::~Sound() {
	reset();
}

Sound& Sound::operator=(const Sound& rhs) {
	if (this != &rhs) {
		reset();
		m_sound = rhs.m_sound;
		m_refCount = rhs.m_refCount;
		if (m_refCount != nullptr)
			(*m_refCount)++;
	}
	return *this;
}

Sound& Sound::operator=(Sound&& rhs) {
	if (this != &rhs) {
		reset();
		m_sound = rhs.m_sound;
		m_refCount = rhs.m_refCount;
		rhs.m_sound = nullptr;
		rhs.m_refCount = nullptr;
	}
	return *this;
}

Mix_Chunk* Sound::loadSound(const std::string& file) {
	if (m_sound != nullptr) {
		reset();
	}
	m_sound = Mix_LoadWAV(file.c_str());
	initRefCounter();
	return m_sound;
}

void Sound::reset() {
	if (m_refCount != nullptr && --(*m_refCount) < 1) {
		Mix_FreeChunk(m_sound);
		delete m_refCount;
	}
	m_sound = nullptr;
	m_refCount = nullptr;
}

void Sound::initRefCounter() {
	if (m_sound == nullptr) {
		std::cerr << "In ba::Resources::Sound::loadSound(). Unable to load audio." << std::endl;
		std::cerr << "Mix_GetError() returns: " << Mix_GetError() << std::endl;
		return;
	}
	m_refCount = new int(1);
}



} // namespace Resources
} // namespace ba