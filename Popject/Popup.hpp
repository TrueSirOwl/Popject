#pragma once

#include "ImageStorage.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <ctime>
#include <sys/timeb.h>
#include <thread>
#include "../shared/Settings.hpp"
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
//#include "../shared/Debug.h"

enum ContentType
{
	IMAGE,
	GIF
};

class Popup
{
private:
	Settings sett;

	ImageStorage ImageLib;
	SDL_Renderer* PopupRenderer;
	SDL_Window* window;
	SDL_Texture* imageTexture;
	SDL_Surface* imageSurface;

	int allowed_disps[3];

	SDL_FRect target;

	SDL_Rect* dispbounds;

	SDL_Thread* sdl_loader;

	IMG_Animation *Gif;
	int Current_image;
	long long last_image;

	std::string ContentPath;

	double resizeFactor;

	ContentType Content;

	struct timeb start;
	struct timeb middle;

	double opacity_random_val;

	double fadeout_steps_random_val;
	double fadeout_time_random_val;
	double fadeout_dimin_per_step;
	double fadeout_step;

	std::random_device rd;
	std::mt19937::result_type seed;
	std::mt19937 rng;

	void create_rng();

	void getImage();
	void scale();
	void place();
	static int getImageT(void* data);
	void renderImage();
	void renderGif();
	void DoImage();
	void DoGIF();
	void FadeOut();
	void GifFadeout();
	void setPopupFadeOutSteps();

	void SetWindowClickThrough();

	void PopupRemoval();

public:
	long long lifetime;

	std::mutex CheckDeath;
	bool death;

	Popup(ImageStorage& src, const Settings popsett, SDL_Rect* displays , SDL_Window* window, SDL_Renderer* renderer);

	void PopUp();
	bool Prep();
	//Popup(SDL_Surface image ,const Settings popsett);

	~Popup();

};

