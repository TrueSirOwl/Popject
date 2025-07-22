#pragma once
#include "Popup.hpp"
#include "random.hpp"
//#include <vector>
//#include "../shared/Settings.h"

class Burster
{
private:
	std::vector<Popup*> burstBuffer;
	ImageStorage IMGLib;

	std::mt19937 rng;

	int	BurstAmt;

	std::vector<Popup*>::iterator Burst_iterator;

	struct timeb last;
	struct timeb now;

	const Settings sett;

	std::uniform_real_distribution<double> burst_random_timing;

public:
	Burster(ImageStorage& src, const Settings _sett, SDL_Rect* displays , SDL_Window* wind, SDL_Renderer* renderer);
	void burst();
	bool burst_prep_check();
	bool checkBurstDone();
	~Burster();
};

