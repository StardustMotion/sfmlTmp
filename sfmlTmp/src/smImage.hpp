#pragma once
#include <array>
#include <string_view>

namespace image {
	//enum class Sprite {};
	// subategories later Tile, Actor, Background, etc etc

	constexpr std::string_view root = "res/img/parallax/";
	//constexpr std::string_view parallax = "parallax/";

	enum Id {
		// Parallax
		BG_MAIN,
		// ...
		IMG_SIZE
	};

	constexpr std::array<std::string_view, static_cast<size_t>(Id::IMG_SIZE)> files {
		"bg.png"
	};
}