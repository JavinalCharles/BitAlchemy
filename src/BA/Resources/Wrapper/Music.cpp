#include <BA/Resources/Wrapper/Music.hpp>


using namespace ba;
using ba::Resources::Music;

Music::Music() = default;

Music::Music(const std::string& file) {
	loadMusic(file);
}

Music::Music(const Music& other) :
	m_music(other.m_music),
	m_refCount(other.m_refCount)
{
	if (m_refCount != nullptr) {
		(*m_refCount)++;
	}
}

Music::Music(Music&& other) :
	m_music(other.m_music),
	m_refCount(other.m_refCount)
{
	other.m_music = nullptr;
	other.m_refCount = nullptr;
}

Music::~Music() {
	reset();
}

Music& Music::operator=(const Music& rhs) {
	if (this != &rhs) {
		reset();
		m_music = rhs.m_music;
		m_refCount = rhs.m_refCount;
		if (m_refCount != nullptr) {
			(*m_refCount)++;
		}
	}
	return *this;
}

Music& Music::operator=(Music&& rhs) {
	if (this != &rhs) {
		reset();
		m_music = rhs.m_music;
		m_refCount = rhs.m_refCount;
		rhs.m_music = nullptr;
		rhs.m_refCount = nullptr;
	}
	return *this;
}

Mix_Music* Music::loadMusic(const std::string& file) {
	if (m_music != nullptr) {
		reset();
	}
	m_music = Mix_LoadMUS(file.c_str());
	initRefCounter();
	return m_music;
}

void Music::reset() {
	if (m_refCount != nullptr && --(*m_refCount) < 1) {
		Mix_FreeMusic(m_music);
		delete m_refCount;
	}
	m_music = nullptr;
	m_refCount = nullptr;
}

void Music::initRefCounter() {
	if (m_music == nullptr) {
		std::cerr << "In ba::Resources::Music::loadMusic(). Unable to load music." << std::endl;
		std::cerr << "Mix_GetError() returns: " << m_music << std::endl;
		return;
	}
	m_refCount = new int(1);
}