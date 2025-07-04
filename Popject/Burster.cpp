#include "Burster.hpp"

/*Creates an amount of Popups which starts the image loading thread for each Popup*/
Burster::Burster(ImageStorage& src, const Settings sett, SDL_Rect* displays , SDL_Window* wind, SDL_Renderer* renderer): IMGLib(src) {
	create_rng();

	std::uniform_int_distribution<int> burst_random_dist(sett.lowMultipop, sett.highMultipop);

	BurstAmt = burst_random_dist(rng);

	for (int i = 0; i < BurstAmt; i++) {
		burstBuffer.push_back(new Popup(IMGLib, sett, displays, wind, renderer));
	}
}

void Burster::create_rng() {
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
}

bool Burster::prep() {
	bool done = true;
	std::vector<Popup*>::iterator it = burstBuffer.begin();
	while (it != burstBuffer.end()) {
		if ((*it)->Prep() == false) {
			done = false;
			//std::cout << "burst not ready yet" << std::endl;
		}
		++it;
	}
	return (done);
}

void Burster::burst() {
	std::vector<Popup*>::iterator it = burstBuffer.begin();
	while (it != burstBuffer.end()) {
		(*it)->PopUp();
		++it;
	}
}

bool Burster::checkBurstDone() {
	std::vector<Popup*>::iterator it = burstBuffer.begin();
	while (it != burstBuffer.end()) {
		if ((*it)->death == true) {
			delete(*it);
			burstBuffer.erase(it);
		} else {
			++it;
		}
	}
	if (burstBuffer.empty() == true) {
		return (true);
	}
	return(false);
}

Burster::~Burster() {
	while (burstBuffer.empty() == false) {
		delete(burstBuffer.back());
		burstBuffer.pop_back();
	}
}