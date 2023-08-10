#pragma once

#include <map>
#include <functional>
#include <utility>

#include "BA/Components/Component.hpp"

namespace ba {

class AI : public Component {
public:
	explicit AI(Entity* owner);

	virtual void behave(float deltaTime) = 0;
public:
	static const IDtype CID;
}; // class AI

} // namespace ba
