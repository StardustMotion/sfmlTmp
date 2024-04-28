#pragma once
#include <vector>
#include <SFML/Graphics/Rect.hpp>

struct Frame {
	const sf::IntRect crop;
};

enum AnimType : std::size_t {
	IDLE,
	Ooof,
	ERF
};

// Wraps a sequence of frames into an actual sequence
class Animation
{
	AnimType type; // identifier/pattern
	std::vector<std::pair<float, Frame>> frames; // [duration, frame] (0 = inf. duration)
public:
	Animation(AnimType type, std::vector<std::pair<float,Frame>>&& frames);
	~Animation();
	const std::vector<std::pair<float, Frame>>& getFrames() const;
};

