#include "BA/Components/AI/ProgrammedAI.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

ProgrammedAI::ProgrammedAI(Entity* owner) :
	AI::AI(owner)
{

}

void ProgrammedAI::behave(float deltaTime) {
	// std::clog << "ProgrammedAI::behave();\n";;
	for (auto& [k, v] : m_behaviorBindings) {
		if (v.first(deltaTime)) {
			for (auto& b : v.second) {
				b(deltaTime);
			}
			break;
		}
	}
}

bool ProgrammedAI::assignBindings(int id, const Condition& condition, const  BehaviorList& behaviorList) {
	return m_behaviorBindings.insert_or_assign(id, std::make_pair(condition, behaviorList)).second;
}

bool ProgrammedAI::assignBindings(int id, const Condition& condition, const Behavior& behavior) {
	return m_behaviorBindings.insert_or_assign(id, std::make_pair(condition, BehaviorList{behavior})).second;
}

bool ProgrammedAI::assignBindings(int id, const std::pair<Condition, BehaviorList>& bindings) {
	return m_behaviorBindings.insert_or_assign(id, bindings).second;
}

void ProgrammedAI::addBehavior(int id, const Behavior& behavior) {
	if (!m_behaviorBindings.contains(id)) {
		throw std::domain_error("ProgrammedAI::addBehavior(id) - BehavioralBindings does not contain a given id.");
	}
	m_behaviorBindings.at(id).second.push_back(behavior);
}

void ProgrammedAI::changeCondition(int id, const Condition& condition) {
	if (!m_behaviorBindings.contains(id)) {
		throw std::domain_error("ProgrammedAI::changeCondition(id) - BehavioralBindings does not contain a given id.");
	}
	m_behaviorBindings.at(id).first = condition;
}

const std::pair<Condition, BehaviorList>& ProgrammedAI::getBindings(int id) const {
	if (!m_behaviorBindings.contains(id)) {
		throw std::domain_error("ProgrammedAI::getBindings(id) - BehavioralBindings does not contain a given id.");
	}
	return m_behaviorBindings.at(id);
}

void ProgrammedAI::removeBindings(int id) {
	if (m_behaviorBindings.contains(id)) {
		m_behaviorBindings.erase(id);
	}
}

const BehavioralBindings& ProgrammedAI::getBehavioralBindings() const {
	return m_behaviorBindings;
}

} // namespace ba