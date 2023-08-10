#pragma once

#include <functional>
#include <vector>
#include "BA/Components/Collidable.hpp"

namespace ba {

using CollidableFunction = std::function<void(IDtype)>;

class FunctionalCollidable : public Collidable {
public:
	explicit FunctionalCollidable(Entity* owner);

	virtual void onCollisionEnter(IDtype other);
	virtual void onCollisionStay(IDtype other);
	virtual void onCollisionExit(IDtype other);

	void addOnCollisionEnter(const CollidableFunction& function);
	void addOnCollisionStay(const CollidableFunction& function);
	void addOnCollisionExit(const CollidableFunction& function);
private:
	std::vector<CollidableFunction> m_exeOnCollisionEnter;
	std::vector<CollidableFunction> m_exeOnCollisionStay;
	std::vector<CollidableFunction> m_exeOnCollisionExit;

}; // class FunctionalCollidable

} // namespace ba
