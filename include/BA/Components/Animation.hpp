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
using SequenceAction = std::function<void(void)>;

struct Frame {
	IDtype								textureID;
	IntRect 							textureRect;
	float								displaySeconds;
	std::forward_list<FrameAction>		actions{};
}; // struct Frame

struct Sequence {
	std::vector<Frame>					frames;
	std::forward_list<SequenceAction>	actions{};
	bool 								looped = false;
}; // struct Sequence

class Animation : public Component {

friend class AnimationSystem;

public:
	Animation(Entity* owner);

	virtual void awake() override;

	void add(IDtype animationID, Sequence sequence);

	void set(IDtype animationID);
	void setLoop(IDtype animationID, bool isLoop = true);
	void setFrame(IDtype animationID, std::size_t frameIndex, const Frame& frame);
	void addFrame(IDtype animationID, const Frame& frame);
	void addFrameAction(IDtype animationID, std::size_t frameIndex, const FrameAction& frameAction);

	void addSequenceAction(IDtype animationID, const SequenceAction& sequenceAction);

	IDtype getCurrentAnimationID() const;
	const Sequence& getCurrentSequence() const;
private:
	std::unordered_map<IDtype, Sequence> m_animationMap;

	IDtype			m_currentAnimation{};
	std::size_t		m_currentFrame{};

	float 			m_currentFrameTime{};

	Sprite*			m_sprite = nullptr;
public:
	static const IDtype CID;
}; // class Animation

} // namespace ba