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

/***********************************************************************
 * @brief Struct to hold information about a single frame of Animation
 * Sequence.
 *
************************************************************************/
struct Frame {
	/// @brief for the Texture
	IDtype							textureID;
	/// @brief of the frame within the texture.
	IntRect 						textureRect;
	/// @brief long the frame will be displayed in seconds.
	float							displaySeconds;
	/// Actions to execute(function call) when transitioning to this frame.
	std::forward_list<FrameAction>	actions{};
}; // struct Frame

/***********************************************************************
 * @brief A struct holding information about a single animation sequence.
 *
************************************************************************/
struct Sequence {
	/// @brief containing each frame for this sequence.
	std::vector<Frame>					frames;
	/// @brief to execute after displaying all the frames.
	std::forward_list<SequenceAction>	actions{};
	/// @brief Whether the sequence should transition to the first frame after
	/// displaySeconds.
	bool 								looped = false;
}; // struct Sequence


/***********************************************************************
 * @brief Holds information about all animations for a single game entity.
 *
 * Note: This component requires Sprite component to work alongside.
************************************************************************/
class Animation : public Component {

friend class AnimationSystem;

public:
	/***********************************************************************
	 * @brief Animation Constructor.
	 *
	 * @param owner Owner of this component.
	************************************************************************/
	explicit Animation(Entity* owner);

	/***********************************************************************
	 * @brief Initializes the attributes and ensures owner has proper
	 * prerequisite.
	 *
	************************************************************************/
	virtual void awake() override;

	/***********************************************************************
	 * @brief Adds a single animation sequence to the object.
	 *
	 * @param animationID the ID that will be used to change the animation of
	 * this object.
	 * @param sequence the animation sequence.
	************************************************************************/
	void add(IDtype animationID, Sequence sequence);

	/***********************************************************************
	 * @brief Changes the current animation of this object to the sequence
	 * referred to by animationID.
	 *
	 * @param animationID the key to the desired animation sequence.
	 *
	 * @throws std::invalid_argument if animationID does not exist as a key for
	 * for this component's animations map.
	************************************************************************/
	void set(IDtype animationID);

	/***********************************************************************
	 * @brief Changes whether to loop the animation sequence referred to by
	 * animationID.
	 *
	 * @param animationID the key to the desired animation sequence.
	 * @param isLoop Boolean attribute whether to loop the sequence or not.
	************************************************************************/
	void setLoop(IDtype animationID, bool isLoop = true);

	/***********************************************************************
	 * @brief Changes a single frame for animation sequence referred to by the
	 * animationID.
	 *
	 * @param animationID the key to the animation sequence to changed.
	 * @param frameIndex the index of the frame to be replaced.
	 * @param frame the frame to replace the old one with.
	************************************************************************/
	void setFrame(IDtype animationID, std::size_t frameIndex, const Frame& frame);

	/***********************************************************************
	 * @brief Appends a new frame at the end of the animation sequence referred
	 * to by animationID.
	 *
	 * @param animationID the key to the desired animation sequence.
	 * @param frame the frame to be appended to the sequence.
	************************************************************************/
	void addFrame(IDtype animationID, const Frame& frame);

	/***********************************************************************
	 * @brief Adds a frame action for a single frame within the animation
	 * sequence referred to by animationID.
	 *
	 * @param animationID the key to the desired animation sequence.
	 * @param frameIndex the index of the frame to add an action to.
	 * @param frameAction the action to be added.
	************************************************************************/
	void addFrameAction(IDtype animationID, std::size_t frameIndex, const FrameAction& frameAction);

	/***********************************************************************
	 * @brief Adds an action to the animation sequence referred to by
	 * animationID.
	 *
	 * @param animationID the key to the desired animation sequence.
	 * @param sequenceAction the action to be added.
	************************************************************************/
	void addSequenceAction(IDtype animationID, const SequenceAction& sequenceAction);

	/***********************************************************************
	 * @brief returns the ID of the current animation sequence being displayed
	 * for this object.
	 *
	 * @return An unsigned integer type which is the ID of the currently
	 * displayed animation sequence.
	************************************************************************/
	IDtype getCurrentAnimationID() const;

	/***********************************************************************
	 * @brief returns a const reference to the current animation sequence.
	 *
	 * @return a reference to the current animation sequence.
	************************************************************************/
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
