#pragma once
#include "Popup.hpp"
//#include <vector>
//#include "../shared/Settings.h"

class Burster
{
private:
	std::vector<Popup*> burstBuffer;
	ImageStorage IMGLib;

	std::random_device rd;
	std::mt19937::result_type seed;
	std::mt19937 rng;
	void create_rng();

	int	BurstAmt;

public:
	Burster(ImageStorage& src, const Settings sett, SDL_Rect* displays , SDL_Window* wind, SDL_Renderer* renderer);
	void burst();
	bool prep();
	bool checkBurstDone();
	~Burster();
};

