#pragma once

#include <memory>
#include <unordered_map>
#include <SDL2/SDL_events.h>

#include <BA/Inputs/Input.hpp>
#include <BA/Types.hpp>

namespace ba {

class InputManager {
public:
	void handleEvents();

	template <typename T>
	std::shared_ptr<T> addInput();

	template <typename T>
	std::shared_ptr<T> getInput();

private:
	std::unordered_map<IDtype, std::shared_ptr<Input>> m_inputs;
}; // class InputManager


template <typename T>
std::shared_ptr<T> InputManager::addInput() {
	// ensure T is derived of ba::Input
	static_assert(std::is_base_of<ba::Input, T>::value, "Error. T must be a derived type of ba::Input. Assertion returned false.");

	if (m_inputs.contains(T::IID)) {
		if (std::dynamic_pointer_cast<T>(m_inputs.at(T::IID))) {
			// T already exists. just rerturn it.
			return std::dynamic_pointer_cast<T>(m_inputs.at(T::IID));
		}
		else {
			// if T does not exist yet, but a similar IID is being used. replace the object mapped to that IID.
			m_inputs.at(T::IID) = std::make_shared<T>(this);
		}
	}
	else {
		m_inputs.insert(std::make_pair(T::IID, std::make_shared<T>(this)));
	}

	return std::dynamic_pointer_cast<T>(m_inputs.at(T::IID));
}

template <typename T>
std::shared_ptr<T> InputManager::getInput() {
	// ensure T is derived of ba::Input
	static_assert(std::is_base_of<ba::Input, T>::value, "Error. T must be a derived type of ba::Input. Assertion returned false.");

	if (m_inputs.contains(T::IID)) {
		return std::dynamic_pointer_cast<T>(m_inputs.at(T::IID));
	}
	return nullptr;
}

} // namespace ba