#include "random.hpp"

std::mt19937 create_rng() {
	std::random_device rd;
	std::mt19937::result_type seed;
	std::mt19937 rng;

	seed = rd() ^ (
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::system_clock::now().time_since_epoch()
		).count() +
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()
		).count() );
	rng = std::mt19937(seed);
	return(rng);
}