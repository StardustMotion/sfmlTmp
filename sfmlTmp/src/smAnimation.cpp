#include "smAnimation.hpp"

Animation::Animation(AnimType type, std::vector<std::pair<float, Frame>>&& frames)
	: type(type)
	, frames(frames) {

}

Animation::~Animation() { ; }

const std::vector<std::pair<float, Frame>>& Animation::getFrames() const {
	return this->frames;
}