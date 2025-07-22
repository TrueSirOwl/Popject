#include "Burster.hpp"

/*Creates an amount of Popups which starts the image loading thread for each Popup*/
Burster::Burster(ImageStorage& src, const Settings _sett, SDL_Rect* displays , SDL_Window* wind, SDL_Renderer* renderer): IMGLib(src), sett(_sett){
	rng = create_rng();

	std::uniform_int_distribution<int> burst_random_dist(sett.lowMultipop, sett.highMultipop);
	burst_random_timing = std::uniform_real_distribution<double>(sett.lowMultipopTiming, sett.highMultipopTiming);

	BurstAmt = burst_random_dist(rng);

	for (int i = 0; i < BurstAmt; i++) {
		burstBuffer.push_back(new Popup(IMGLib, sett, displays, wind, renderer));
	}
}
 
bool Burster::burst_prep_check() {
	bool done = true;
	std::vector<Popup*>::iterator it = burstBuffer.begin();
	while (it != burstBuffer.end() && (*it)->PrepFinished == false) {
		(*it)->Popup_prep();
		done = (*it)->PrepFinished;
		++it;
	}
	if (done == true) {
		this->Burst_iterator = burstBuffer.begin();
		ftime(&last);
	}
	return (done);
}

void Burster::burst() {
	ftime(&now);
	std::vector<Popup*>::iterator it = burstBuffer.begin();
	if ((now.time * 1000 + now.millitm) - (last.time * 1000 + last.millitm) > burst_random_timing(rng)) {
		if (Burst_iterator != burstBuffer.end()) {
			++Burst_iterator;
			last = now;
		}
	}
	while (it != Burst_iterator && it != burstBuffer.end()) {
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