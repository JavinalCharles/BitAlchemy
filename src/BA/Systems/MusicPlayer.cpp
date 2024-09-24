#include <BA/Systems/MusicPlayer.hpp>

namespace ba {

using ba::Resources::Music;
using ba::Resources::MusicManager;
namespace fs = std::filesystem;

MusicPlayer::MusicPlayer() = default;

MusicPlayer::MusicPlayer(MusicManager* mm) :
	m_musicManager(mm)
{

}

void MusicPlayer::update() {
	if (m_musicManager == nullptr || !m_playing) {
		return;
	}

	if (Mix_PlayingMusic() == 0) {
		// No music is playing
		playNext();
	}
	else if (Mix_PausedMusic() != 0) {
		// Music is playing, but is paused
		Mix_ResumeMusic();
	}
}

IDtype MusicPlayer::addMusic(const std::string& fileName) {
	if(m_musicManager == nullptr){
		return 0;
	}

	std::optional<fs::path> musicPath = m_musicManager->findFile(fileName);
	if (!musicPath.has_value()) {
		return 0;
	}

	IDtype id = m_musicManager->create(musicPath.value());

	// IDtype id = m_resources->loadMusic(fileName);
	m_musicList.push_back(id);
	if (m_currentMusic == m_musicList.end()) {
		m_currentMusic = m_musicList.begin();
	}

	return id;
}

void MusicPlayer::addMusic(IDtype musicID) {
	if(m_musicManager == nullptr) {
		return;
	}

	Mix_Music* music = m_musicManager->at(musicID).get();
	if(music == NULL) {
		return;
	}
	m_musicList.push_back(musicID);
	if (m_currentMusic == m_musicList.end()) {
		m_currentMusic = m_musicList.begin();
	}
}

IDtype MusicPlayer::playAsNext(const std::string& fileName) {
	if(m_musicManager == nullptr) {
		return 0;
	}
	IDtype id;
	if(m_musicList.size() <= 1) {
		id = addMusic(fileName);
	}
	else {
		std::optional<fs::path> musicPath = m_musicManager->findFile(fileName);
		if (!musicPath.has_value()) {
			return 0;
		}
		id = m_musicManager->create(musicPath.value());
		auto nextIter = m_currentMusic;
		++nextIter;
		m_musicList.insert(nextIter, id);
	}
	return id;
}

void MusicPlayer::playAsNext(IDtype musicID) {
	if(m_musicManager == nullptr) {
		return;
	}
	if(m_musicList.size() <= 1) {
		addMusic(musicID);
	}
	else {
		Mix_Music* music = m_musicManager->at(musicID).get();
		if (music != NULL) {
			auto nextIter = m_currentMusic;
			++nextIter;
			m_musicList.insert(nextIter, musicID);
		}
	}
}

void MusicPlayer::play() {
	if(m_musicList.empty()) {
		return;
	}
	m_playing = true;
	if(Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(m_musicManager->at(*m_currentMusic).get(), 0);
	}
	else if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}

void MusicPlayer::playNext() {
	if(m_musicList.empty()) {
		return;
	}
	m_playing = true;
	incrementIterator();
	if(m_playing)
		Mix_PlayMusic(m_musicManager->at(*m_currentMusic).get(), 0);
}

void MusicPlayer::playPrevious() {
	if(m_musicList.empty()) {
		return;
	}
	m_playing = true;
	decrementIterator();
	
	Mix_PlayMusic(m_musicManager->at(*m_currentMusic).get(), 0);
}

void MusicPlayer::playFirst() {
	if (m_musicList.empty()) {
		return;
	}
	m_currentMusic = m_musicList.begin();
	m_playing = true;
	Mix_PlayMusic(m_musicManager->at(*m_currentMusic).get(), 0);
}

void MusicPlayer::pause() {
	m_playing = false;
	Mix_PauseMusic();
}

void MusicPlayer::stop() {
	m_playing = false;
	Mix_HaltMusic();
}

void MusicPlayer::setLooping(bool looping) {
	m_looping = looping;
}

bool MusicPlayer::isLooping() const {
	return m_looping;
}

void MusicPlayer::clearMusicList() {
	Mix_HaltMusic();
	m_playing = false;
	
	m_musicList.clear();
}

void MusicPlayer::setMusicManager(MusicManager* mm) {
	m_musicManager = mm;
}

void MusicPlayer::incrementIterator() {
	if (m_currentMusic != m_musicList.end()) {
		++m_currentMusic;
	}

	if (m_currentMusic == m_musicList.end()) {
		if (m_looping) {
			m_currentMusic = m_musicList.begin();
		}
		else {
			m_playing = false;
			Mix_HaltMusic();
		}
	}
}

void MusicPlayer::decrementIterator() {
	if (m_currentMusic != m_musicList.begin()) {
		--m_currentMusic;
	}
}

} // namespace ba