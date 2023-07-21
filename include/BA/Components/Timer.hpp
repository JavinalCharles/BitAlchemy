#pragma once

#include <functional>
#include <map>
#include <stdexcept>
#include <utility>
#include "BA/Components/Component.hpp"
#include "BA/Types.hpp"

namespace ba {

struct TimedAction {
	float timeToActivate;
	std::function<void(void)> action;
	bool isLoop = false;
	float elapsedTime = 0.0f;
};

class Timer : public Component {
public:
	friend class TimerSystem;
	static const IDtype CID;

	Timer(Entity* owner);

	IDtype setTimer(const std::function<void(void)>& action, float time, bool isLooped = false);
	std::pair<std::function<void(void)>, float> getTimedAction(IDtype actionID) const;

protected:
	std::map<IDtype, TimedAction>& getTimedActions();

private:
	std::map<IDtype, TimedAction>	m_timedActions;
	IDtype m_insertions = 0u;
}; // class Component

} // namespace ba