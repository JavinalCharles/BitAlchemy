#pragma once

#include <functional>
#include <forward_list>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <iostream>


#include <BA/Components/Sprite.hpp>
#include <BA/Types.hpp>

namespace ba {

using FrameAction = std::function<void(void)>;

struct Frame {
	IDtype								textureID;
	IntRect 							textureRect;
	float								displaySeconds;
	std::forward_list<FrameAction>		actions;
}; // struct Frame

struct Sequence {
	std::vector<Frame>	frames;
	bool 				looped = false;
}; // struct Sequence

class Animation : public Component {

friend class AnimationSyste;

public:

	Animation(Entity* owner);

	virtual void awake() override;

	void add(IDtype animationID, Sequence sequence);

	void set(IDtype animationID);

	IDtype getCurrentAnimationID() const;
	const Sequence& getCurrentSequence() const;
private:
	std::unordered_map<IDtype, Sequence> m_animationMap;

	IDtype			m_currentAnimation{};
	std::size_t		m_currentFrame{};

	float 			m_currentFrameTime{};

	Sprite*			m_sprite = nullptr;
public:
	static const IDtype CID = ComponentID::ANIMATION;
}; // class Animation

} // namespace ba