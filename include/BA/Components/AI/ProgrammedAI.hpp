#pragma once

#include "BA/Components/AI/AI.hpp"


namespace ba {

using Condition = std::function<bool(float)>;
using Behavior = std::function<void(float)>;
using BehaviorList = std::vector<Behavior>;

// Bindings between condition and behavior, arranged by an integer key
using BehavioralBindings = std::map<int, std::pair<Condition, BehaviorList>>;

class ProgrammedAI : public AI {
public:
	explicit ProgrammedAI(Entity* owner);

	virtual void behave(float deltaTime) override;

	bool assignBindings(int id, const Condition& condition, const BehaviorList& behaviorList);
	bool assignBindings(int id, const Condition& condition, const Behavior& behavior);
	bool assignBindings(int id, const std::pair<Condition, BehaviorList>& bindings);

	void addBehavior(int id, const Behavior& behavior);
	void changeCondition(int id, const Condition& condition);

	const std::pair<Condition, BehaviorList>& getBindings(int id) const;
	void removeBindings(int id);


	const BehavioralBindings& getBehavioralBindings() const;

private:
	BehavioralBindings 		m_behaviorBindings;
}; // class AI

} // namespace ba
