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

double flat_real_random(std::mt19937& rng, double min, double max) {
	std::uniform_real_distribution<double> dist(min, max);
	return(dist(rng));
}

int flat_int_random(std::mt19937& rng, int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return(dist(rng));
}

int weighted_int_random(std::mt19937& rng, int min, int _max, double weight, double strength = 1) {
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double max = _max + 1;  // keep as double for calculations
	double u = dist(rng);

	double range = max - min;
	double pos = (weight - min) / range;  // position of the weight relative to range
	double u_mod = std::pow(u, strength);

	int raw_result = 0;

	if (u_mod < pos) {
		// lower half: map u_mod from [0, pos] to [min, weight]
		raw_result = static_cast<int>(min + (weight - min) * std::sqrt(u_mod / pos));
	} else {
		// upper half: map u_mod from [pos, 1] to [weight, max]
		raw_result = static_cast<int>(weight + (max - weight) * (1 - std::sqrt((1 - u_mod) / (1 - pos))));
	}

	int result = raw_result;
	if (result < min) result = min;
	if (result > _max) result = _max;

	return result;
}



double weighted_real_random(std::mt19937& rng, double min, double max, double weight, double strength = 1 ) {
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double u = dist(rng);

	double c = (weight - min) / (max - min);
	double u_mod = std::pow(u, strength);

	if (u_mod < c) {
		return min + std::sqrt(u_mod * (max - min) * (weight - min));
	} else {
		return max - std::sqrt((1 - u_mod) * (max - min) * (max - weight));
	}
}

#include <iostream>
#include <random>
#include <map>
#include <algorithm> // for std::max_element

// Your weighted_int_random function here (assumed defined)

std::map<int, int> run_weighted_int_distribution(std::mt19937& rng, int min, int max, double weight, double strength, int samples) {
	std::map<int, int> frequency;

	for (int i = 0; i < samples; ++i) {
		int value = weighted_int_random(rng, min, max, weight, strength);
		frequency[value]++;
	}

	return frequency;
}

int run( double weight, double strength) {
	std::mt19937 rng(std::random_device{}());

	int min = 1;
	int max = 20;
	int samples = 1000000;

	auto result = run_weighted_int_distribution(rng, min, max, weight, strength, samples);

	// Find max frequency to scale histogram bars
	int max_freq = 0;
	for (int i = min; i <= max; ++i) {
		max_freq = std::max(max_freq, result[i]);
	}

	const int bar_width = 50; // max characters for the longest bar

	std::cout << "Value\tFrequency\tPercent\tHistogram\n";
	for (int i = min; i <= max; ++i) {
		int bar_len = static_cast<int>((static_cast<double>(result[i]) / max_freq) * bar_width);
		double pct = 100.0 * result[i] / samples;
		std::cout << i << "\t" << result[i] << "\t" << pct << "%\t" << std::string(bar_len, '#') << "\n";
	}

	return 0;
}

// int main(void) {
// 	for (int i = 0; i <= 20; i++) {
// 		std::cout << "Strength: "<< i <<"=================================================" << std::endl;
// 		run( 5, i);
// 	}
// }