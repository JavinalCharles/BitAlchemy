#pragma once

#include "BA/Components/Component.hpp"

namespace ba {

class Collidable : public Component {
public:
	explicit Collidable(Entity* owner);

	virtual void onCollisionEnter(IDtype other) = 0;
	virtual void onCollisionStay(IDtype other) = 0;
	virtual void onCollisionExit(IDtype other) = 0;
private:

public:
	static const IDtype CID;

}; // class Collidable

} // namespace ba
