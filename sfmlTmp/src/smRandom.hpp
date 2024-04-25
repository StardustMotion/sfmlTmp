#pragma once
#include <chrono>
#include <random>

// Courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	inline std::mt19937 generate()
	{
		std::random_device device{};
		std::seed_seq seedSequence {
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				device(), device(), device(), device() };

		return std::mt19937{ seedSequence };
	}

	inline std::mt19937 rng{ generate() };

	inline int get(int min, int max) {
		return std::uniform_int_distribution{ min, max }(rng);
	}
}