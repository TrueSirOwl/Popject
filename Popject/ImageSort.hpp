#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_blendmode.h>
#include "ImageStorage.hpp"
#include "Settings.hpp"
#include <unistd.h>
#include <string>
#include <signal.h>
#include <queue>
#include "Burster.hpp"
#include "random.hpp"
#include <filesystem>
#include <unordered_set>

class ImageSort
{
private:
	/* data */
public:
	ImageSort(/* args */);
	~ImageSort();
	void content_sorting_routine(Settings* Sett);
};

void content_sorting_routine(Settings* Sett);