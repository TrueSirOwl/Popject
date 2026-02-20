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
	Settings* Sett;

	ImageStorage IMGLib;


	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_FRect target;
	SDL_FRect Keep_Button;
	SDL_FRect Delete_Button;
	SDL_FRect Progrees_Bar;

	std::unordered_set<std::string> seen;

	std::string IMGPath;

	SDL_Surface* imageSurface;
	SDL_Texture* imageTexture;

	int window_width;
	int window_height;

	int mousex;
	int mousey;
	bool running = true;

	void getNewImage();

	int IMGLib_size;

public:
	ImageSort(Settings* Sett);
	~ImageSort();
	void content_sorting_routine();
};