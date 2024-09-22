#pragma once

#include <unordered_map>

#include <BA/Resources/Wrapper/Font.hpp>
#include <BA/Resources/Wrapper/Music.hpp>
#include <BA/Resources/Wrapper/Sound.hpp>
#include <BA/Resources/Wrapper/Texture.hpp>
#include <tinyxml2/tinyxml2.h>
#include <BA/Types.hpp>

namespace ba {
namespace Resources {

	/**
	 * @brief A template class for managing a specific type of resource.
	 * 
	 * @tparam Res The Resource Type that the ResourceManger is 
	 * intended to manage.
	 */
	template <typename Res>
	class ResourceManager {
	public:
		/// @brief Default Constructor
		ResourceManager();

		/**
		 * @brief Creates an object of Res.
		 * 
		 * Creates an object by forwarding args to Res's constructor,
		 * emplaces the object to the map and returns the key.
		 * 
		 * @param args arguments to forward to Res's constructor.
		 * @return IDtype The key to the newly created Res.
		 */
		template<typename... Args>
		IDtype create(Args... args);

		///@{
		/**
		 * @brief Provides a reference to a mapped value of Res with
		 * specified key.
		 * 
		 * @param key The key to the object.
		 * @return A reference to the mapped value.
		 * @throws std::out_of_range if the key does not exist.
		 */
		const Res& at(const IDtype& key) const throw(std::out_of_range);
		Res& at(const IDtype& key) throw(std::out_of_range);
		///@}

		std::size_t erase(const IDtype& id);
		void clear();

		std::size_t size() const;
		bool empty() const;
	private:
		std::unordered_map<IDtype, Res> m_map;
		IDtype m_count = 0u;
	}; // class ResourceManager


	///@{
	/// Public Typedefs of ResourceManager
	using FontManager		= ResourceManager<ba::Resources::Font>;
	using MusicManager		= ResourceManager<ba::Resources::Music>;
	using SoundManager		= ResourceManager<ba::Resources::Sound>;
	using TextureManager	= ResourceManager<ba::Resources::Texture>;
	///@}

	template <typename Res>
	ResourceManager<Res>::ResourceManager() = default;
	
	template <typename Res>
	template <typename... Args>
	IDtype ResourceManager<Res>::create(Args... args) {
		m_map.emplace(++m_count, args...);
		return m_count;
	}

	template <typename Res>
	const Res& ResourceManager<Res>::at(const IDtype& key) const {
		return m_map.at(key);
	}

	template <typename Res>
	Res& ResourceManager<Res>::at(const IDtype& key) {
		return m_map.at(key);
	}

	template <typename Res>
	std::size_t ResourceManager<Res>::erase(const IDtype& key) {
		return m_map.erase(key);
	}

	template <typename Res>
	void ResourceManager<Res>::clear() {
		m_map.clear();
	}

	template <typename Res>
	std::size_t ResourceManager<Res>::size() const {
		return m_map.size();
	}

	template <typename Res>
	bool ResourceManager<Res>::empty() const {
		return m_map.empty();
	}

} // namespace Resources
} // namespace ba