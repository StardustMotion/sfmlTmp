#pragma once
#include <string_view>
#include <array>

namespace audio {
	constexpr std::string_view root = "res/audio/";
	enum class BGM {
		MAIN,
		MAIN2,
		BGM_SIZE
	};
	constexpr static std::array<std::string_view, static_cast<size_t>(BGM::BGM_SIZE)> bgm {
		"main.ogg",
		"main2.ogg"
	};
	enum class SFX {
		MET,
		DASH,
		SFX_SIZE
	};
	constexpr std::array <std::string_view, static_cast<size_t>(SFX::SFX_SIZE)> sfx{
		"met.wav",
		"dash.ogg"
	};
}