#pragma once

#include <BA/Utilities/Rect.hpp>

namespace ba {

class Boundable {
public:
	virtual FloatRect getLocalBounds() const = 0;
	virtual FloatRect getGlobalBounds() const = 0;

};

} // namespace ba