#pragma once

#include <list>
#include <BA/ResourceManager.hpp>

namespace ba {

class MusicPlayer {
public:
	MusicPlayer();
	MusicPlayer(ResourceManager* resources);

	void update();

	IDtype addMusic(const std::string& fileName);
	void addMusic(IDtype musicID);
	IDtype playAsNext(const std::string& fileName);
	void playAsNext(IDtype musicID);


	void play();
	void playNext();
	void playPrevious();
	void playFirst();
	void pause();
	void stop();

	void setLooping(bool looping = true);
	bool isLooping() const;

	void clearMusicList();

	void setResourceManager(ResourceManager* rm);
private:
	void incrementIterator();
	void decrementIterator();

	std::list<IDtype>				m_musicList;

	std::list<IDtype>::iterator 	m_currentMusic = m_musicList.end();
	bool							m_playing = false;
	bool							m_looping = false;

	ResourceManager*				m_resources = nullptr;
}; // class MusicPlayer

} // namespace ba