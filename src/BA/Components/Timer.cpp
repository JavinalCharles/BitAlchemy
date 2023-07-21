#include "BA/Components/Timer.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Systems/TimerSystem.hpp"


namespace ba {

const IDtype Timer::CID = ba::ComponentID::TIMER;

Timer::Timer(Entity* owner) :
	Component::Component(owner)
{

}

IDtype Timer::setTimer(const std::function<void(void)>& action, float time, bool isLooped) {
	m_timedActions.insert_or_assign(m_insertions++, TimedAction{time, action, isLooped});

	return m_insertions-1;
}

std::pair<std::function<void(void)>, float> Timer::getTimedAction(IDtype actionID) const {
	if (!m_timedActions.contains(actionID)) {
		throw std::domain_error("Timer does not have an action with specified ID.");
	}
	return std::make_pair(m_timedActions.at(actionID).action, m_timedActions.at(actionID).timeToActivate);
}

std::map<IDtype, TimedAction>& Timer::getTimedActions() {
	return m_timedActions;
}

} // namespace ba