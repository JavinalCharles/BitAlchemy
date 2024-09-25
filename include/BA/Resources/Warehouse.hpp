#pragma once

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

#include <SDL2/SDL_filesystem.h>

#include <BA/Resources/ResourceManager.hpp>

namespace ba {
namespace Resources {

	template <typename T>
	concept ValidResourceManager = requires {
		typename T::Resource;
	} && std::is_base_of_v<PathFinder, T> && std::is_same_v<T, ResourceManager<typename T::Resource>>;

	/**
	 * @brief Warehouse oversees the management of resources.
	 * 
	 */
	class Warehouse {
	public:
		Warehouse();

		~Warehouse();

		template <ValidResourceManager RM>
		RM& includeResourceManager();

		template <ValidResourceManager RM>
		RM& getManager();

		void clear();
	private:
		std::unordered_map<std::type_index, std::unique_ptr<PathFinder>> m_managers;
	}; // class Warehouse

	template <ValidResourceManager RM>
	RM& Warehouse::includeResourceManager() {
		std::type_index index(typeid(RM));

		if (!m_managers.contains(index)) {
			m_managers.emplace(index, std::make_unique<RM>());
		}

		return *dynamic_cast<RM*>(m_managers.at(index).get());
	}

	template <ValidResourceManager RM>
	RM& Warehouse::getManager() {
		std::type_index index(typeid(RM));

		if (!m_managers.contains(index)) {
			m_managers.emplace(index, std::make_unique<RM>());
		}

		return *dynamic_cast<RM*>(m_managers.at(index).get());
	}
} // namespace Resources
}; // namespace ba