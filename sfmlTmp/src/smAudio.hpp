#pragma once
#include <string_view>
#include <array>

namespace audio {
	enum class BGM {
		MAIN,
		MAIN2,
		BGM_SIZE
	};
	constexpr static std::array<std::string_view, static_cast<size_t>(BGM::BGM_SIZE)> bgm {
		"res/audio/main.ogg",
		"res/audio/main2.ogg"
	};
	enum class SFX {
		MET,
		DASH,
		SFX_SIZE
	};
	constexpr std::array <std::string_view, static_cast<size_t>(SFX::SFX_SIZE)> sfx{
		"res/audio/met.wav",
		"res/audio/dash.ogg"
	};
}