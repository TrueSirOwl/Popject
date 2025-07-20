#include "Popup.hpp"
#include <algorithm>
#include <SDL3/SDL_thread.h>

Popup::Popup(ImageStorage& src, const Settings popsett, SDL_Rect* displays , SDL_Window* wind, SDL_Renderer* renderer): 
sett(popsett), ImageLib(src), death(false), dispbounds(displays),
Current_image(0), imageSurface(NULL), imageTexture(NULL), Gif(NULL), Content(IMAGE), last_image(0), window(wind), PopupRenderer(renderer) {
	create_rng();
	this->start = {};
	this->middle = {};
	std::uniform_real_distribution<double> fadeout_steps_random_dist(this->sett.lowPopupFadeOutSteps, this->sett.highPopupFadeOutSteps);
	std::uniform_real_distribution<double> fadeout_time_random_dist(this->sett.lowPopupFadeOutTime, this->sett.highPopupFadeOutTime);
	std::uniform_real_distribution<double> opacity_random_dist(this->sett.lowPopupOpacity, this->sett.highPopupOpacity);
	std::uniform_real_distribution<double> lifespan_random_dist(this->sett.lowPopupLifespan, this->sett.highPopupLifespan);

	fadeout_steps_random_val = fadeout_steps_random_dist(rng);
	fadeout_time_random_val = fadeout_time_random_dist(rng);
	opacity_random_val = opacity_random_dist(rng);
	lifetime = lifespan_random_dist(rng);

	this->fadeout_dimin_per_step = opacity_random_val / fadeout_steps_random_val;
	this->fadeout_step = fadeout_time_random_val / fadeout_steps_random_val;
	sdl_loader = SDL_CreateThread(getImageT, "loader", this);
}


void Popup::create_rng() {
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

int Popup::getImageT(void* data) {
	Popup* dota = static_cast<Popup*>(data);
	dota->getImage();
	return(0);
}


void Popup::getImage()
{
	this->ContentPath = ImageLib.getRandomImage();
	if (this->ContentPath.substr(this->ContentPath.find_last_of('.') + 1) == "gif") {
		this->Gif = IMG_LoadAnimation(this->ContentPath.c_str());
		this->Content = GIF;
	}
	this->imageSurface = IMG_Load(this->ContentPath.c_str());
	if (this->imageSurface == NULL) {
		LOG(WARNING, this->sett.LoggingStrenght, "Loading " + this->ContentPath + " Failed: " + (std::string)SDL_GetError());
		exit(1);
	}
}

void Popup::scale() {
	double targetSize;
	std::uniform_real_distribution<double> scaleFactor(this->sett.lowImageScale, this->sett.highImageScale);
	targetSize = scaleFactor(rng);
	double scaleW = dispbounds[0].w * targetSize / imageSurface->w;
	double scaleH = dispbounds[0].h * targetSize / imageSurface->h;
	this->resizeFactor = std::min(scaleW, scaleH);
	this->target.w = static_cast<int>(this->imageSurface->w * resizeFactor);
	this->target.h = static_cast<int>(this->imageSurface->h * resizeFactor);
}

void Popup::place() {
	std::uniform_int_distribution<int> WhereH(0, dispbounds[0].h - this->target.h);
	std::uniform_int_distribution<int> WhereW(0, dispbounds[0].w - this->target.w);
	//std::uniform_int_distribution<int> WhereH(0, 1080 - this->target.h);
	//std::uniform_int_distribution<int> WhereW(0, 1920 - this->target.w);
	this->target.x = WhereW(rng);
	this->target.y = WhereH(rng);
}

bool Popup::Prep() {
	if (SDL_GetThreadState(this->sdl_loader) == SDL_THREAD_COMPLETE) {
		SDL_WaitThread(this->sdl_loader,NULL);
		this->sdl_loader = NULL;
		//std::cout << "ready\n" << std::flush;
	} else if (this->sdl_loader != NULL) {
		//std::cout << "unready\n" << std::flush;
		return (false);
	}
	scale();
	place();
	SDL_SetSurfaceAlphaMod(this->imageSurface, opacity_random_val * 255);
	if (this->imageTexture != NULL) {
		SDL_DestroyTexture(this->imageTexture);
		this->imageTexture = NULL;
	}
	if (imageSurface == NULL) {
		std::cout << "surface is NULL" << std::endl;
	}
	this->imageTexture = SDL_CreateTextureFromSurface(this->PopupRenderer,this->imageSurface);
	if (this->imageTexture == NULL) {
		LOG(HERROR, this->sett.LoggingStrenght ,SDL_GetError());
		SDL_ClearError();
	}
	SDL_SetTextureBlendMode(this->imageTexture, SDL_BLENDMODE_BLEND);
	return (true);
}

void Popup::PopUp() {
	if (start.time == 0 && start.millitm == 0) {
		ftime(&start);
	}

	switch (this->Content) {
	case (GIF):
		DoGIF();
		break;
	case (IMAGE):
		DoImage();
		break;
	default:
		break;
	}
}

void Popup::DoGIF() {
	struct timeb now;
	ftime(&now);
	if (((long long)now.time * 1000 + now.millitm) - ((long long)start.time * 1000 + start.millitm) > this->lifetime) {
		if (this->sett.PopupFadeOut == true) {
			GifFadeout();
		}
	} else {
		renderGif();
	}
}

void Popup::DoImage() {
	struct timeb now;
	ftime(&now);
	if (((long long)now.time * 1000 + now.millitm) - ((long long)start.time * 1000 + start.millitm) > this->lifetime) {
		if (this->sett.PopupFadeOut == true) {
			FadeOut();
		}
	} else {
		SDL_RenderTexture(this->PopupRenderer, this->imageTexture, NULL, &this->target);
	}
}

void Popup::renderGif() {
	struct timeb now;
	ftime(&now);
	if (this->Current_image >= Gif->count) {
		this->Current_image = 0;
	}
	if (((long long)now.time * 1000 + now.millitm) - this->last_image >= Gif->delays[this->Current_image]) {
		if (this->imageTexture != NULL) {
			SDL_DestroyTexture(this->imageTexture);
			this->imageTexture = NULL;
		}
		this->imageTexture = SDL_CreateTextureFromSurface(this->PopupRenderer, Gif->frames[this->Current_image++]);
		SDL_SetTextureBlendMode(this->imageTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(this->imageTexture, opacity_random_val * 255);
		SDL_RenderTexture(this->PopupRenderer, this->imageTexture, NULL, &this->target);
		this->last_image = (long long)now.time * 1000 + now.millitm;
	} else {
		SDL_SetTextureAlphaMod(this->imageTexture, opacity_random_val * 255);
		SDL_RenderTexture(this->PopupRenderer, this->imageTexture, NULL, &this->target);
	}
}

void Popup::GifFadeout() {
	struct timeb middle1;

	ftime(&middle1);

	if (opacity_random_val != 0) {
		if ((middle1.time * 1000 + middle1.millitm) - (middle.time * 1000 + middle.millitm) >= fadeout_step) {
			double stepmult = (((middle1.time * 1000 + middle1.millitm) - (middle.time * 1000 + middle.millitm)) / fadeout_step);
			if (stepmult > 10000) {
				stepmult = 1;
			}
			opacity_random_val -= fadeout_dimin_per_step * stepmult;
			if (opacity_random_val < 0) {
				opacity_random_val = 0;
			}
			renderGif();
			middle = middle1;
		} else {
			renderGif();
		}
	} else {
		this->death = true;
	}
}

void Popup::FadeOut() {
	struct timeb middle1;

	ftime(&middle1);

	if (opacity_random_val != 0) {
		if ((middle1.time * 1000 + middle1.millitm) - (middle.time * 1000 + middle.millitm) >= fadeout_step) {
			double stepmult = (((middle1.time * 1000 + middle1.millitm) - (middle.time * 1000 + middle.millitm)) / fadeout_step);
			if (stepmult > 10000) {
				stepmult = 1;
			}
			opacity_random_val -= fadeout_dimin_per_step * stepmult;
			if (opacity_random_val < 0) {
				opacity_random_val = 0;
			}
			SDL_SetTextureAlphaMod(this->imageTexture, opacity_random_val * 255);
			SDL_RenderTexture(this->PopupRenderer, this->imageTexture, NULL, &this->target);
			middle = middle1;
		} else {
			SDL_RenderTexture(this->PopupRenderer, this->imageTexture, NULL, &this->target);
		}
	} else {
		this->death = true;
	}
}

void Popup::PopupRemoval() {
	std::string trashpath = sett.TrashbinPath;
	std::cout << ContentPath << std::endl;
	trashpath.append(ContentPath.substr(ContentPath.find_last_of('/')));
	std::cout << trashpath << std::endl;
	//std::filesystem::rename(this->ContentPath,trashpath);
}

Popup::~Popup() {
	//std::cout << "Popup vaporised" << std::endl;
	if (this->imageSurface != NULL) {
		SDL_DestroySurface(this->imageSurface);
		this->imageSurface = NULL;
	}
	if (this->imageTexture != NULL) {
		SDL_DestroyTexture(this->imageTexture);
		this->imageTexture = NULL;
	}
	if (this->Gif != NULL) {
		IMG_FreeAnimation (this->Gif);
		this->Gif = NULL;
	}
}