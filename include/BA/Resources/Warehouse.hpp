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
	} && std::is_base_of_v<RMBase, T> && std::is_same_v<T, ResourceManager<typename T::Resource>>;

	/**
	 * @brief A single class to managed all resources and filesystem.
	 * 
	 */
	class Warehouse {
	public:
		Warehouse();

		~Warehouse();

		template <ManageableResource R>
		ResourceManager<R>& includeResourceManager();

		template <ValidResourceManager RM>
		RM& includeResourceManager();

		template <ManageableResource R>
		ResourceManager<R>& getManager();

		template <ValidResourceManager RM>
		RM& getManager();

	private:
		std::unordered_map<std::type_index, std::unique_ptr<RMBase>> m_managers;
	}; // class Warehouse

	template <ManageableResource R>
	ResourceManager<R>& Warehouse::includeResourceManager() {
		return includeResourceManager<ResourceManager<R>>();
	}

	template <ValidResourceManager RM>
	RM& Warehouse::includeResourceManager() {
		std::type_index index(typeid(RM::Resource));

		if (!m_managers.contains(index)) {
			m_managers.emplace(index, std::make_unique<RM>());
		}

		return *std::dynamic_pointer_cast<RM>(m_managers.at(index));
	}

	template <ManageableResource R>
	ResourceManager<R>& Warehouse::getManager() {
		return getManager<ResourceManager<R>>();
	}

	template <ValidResourceManager RM>
	RM& Warehouse::getManager() {
		std::type_index index(typeid(RM::Resource));

		if (!m_managers.contains(index)) {
			m_managers.emplace(index, std::make_unique<RM>());
		}

		return *std::dynamic_pointer_cast<RM>(m_managers.at(index));
	}
} // namespace Resources
}; // namespace ba