#include "ImageSort.hpp"
#include "ImageStorage.hpp"

ImageSort::ImageSort(Settings* Settings): Sett(Settings), IMGLib(ImageStorage(Sett->ImageFolderPath)) {
	IMGLib_size = IMGLib.get_Lib_size();
	imageSurface = NULL;
	imageTexture = NULL;
}

ImageSort::~ImageSort() {
	if (this->imageSurface != NULL) {
		SDL_DestroySurface(this->imageSurface);
		this->imageSurface = NULL;
	}
	if (this->imageTexture != NULL) {
		SDL_DestroyTexture(this->imageTexture);
		this->imageTexture = NULL;
	}
	if (this->window != NULL) {
		SDL_DestroyWindow(this->window);
		this->window = NULL;
	}
	if (this->renderer != NULL) {
		SDL_DestroyRenderer(renderer);
		this->renderer = NULL;
	}
}


void ImageSort::content_sorting_routine() {
	SDL_CreateWindowAndRenderer("Content_sorting",1000, 900, 0, &window,&renderer);
	
	SDL_Event event;

	target.w = 1000;
	target.h = 850;
	target.x = 0;
	target.y = 0;
	

	IMGPath = IMGLib.getRandomImage();
	imageSurface = IMG_Load(IMGPath.c_str());
	target.w = imageSurface->w;
	target.h = imageSurface->h;
	SDL_SetWindowSize(window, target.w, target.h+50);
	imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_SetWindowResizable(window, true);
	SDL_SetWindowAlwaysOnTop(window,true);

	while (running == true) {
		SDL_Delay(1);
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_MOUSE_BUTTON_DOWN:

				SDL_GetWindowSize(window, &window_width, &window_height);
				mousex = event.button.x;
				mousey = event.button.y;
				if (mousey > window_height-50 && mousex >= window_width/2) {
					getNewImage();
				}
				if (mousey > window_height-50 && mousex < window_width/2) {
					std::string filename = IMGPath.substr(IMGPath.find_last_of('/'));
					std::cout << "trash path: " << Sett->TrashbinPath << std::endl;
					std::cout << "filename: " << filename << std::endl;
					std::string newpath = Sett->TrashbinPath + filename;
					std::filesystem::copy_file(IMGPath, newpath);
					std::filesystem::remove(IMGPath);
					getNewImage();
				}
				break;
			case SDL_EVENT_QUIT:
				running = false;
				std::cout << "quitting" << std::endl;
				break;

			default:
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		int w = 0;
		int h = 0;
		SDL_GetWindowSize(window, &w, &h);
		target.w = w;
		target.h = h - 50;
		Keep_Button.x = w / 2;
		Keep_Button.y = h - 40;
		Keep_Button.w = w / 2;
		Keep_Button.h = 40;
		Delete_Button.x = 0;
		Delete_Button.y = h - 40;
		Delete_Button.w = w / 2;
		Delete_Button.h = 40;
		Progrees_Bar.x = 0;
		Progrees_Bar.y = h - 50;
		double norm = static_cast<double>(seen.size()) / IMGLib_size;
		Progrees_Bar.w = norm * w;
		Progrees_Bar.h = 10;
		SDL_RenderTexture(renderer, imageTexture, NULL, &target);
		SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
		SDL_RenderFillRect(renderer, &Keep_Button);
		SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
		SDL_RenderFillRect(renderer, &Delete_Button);
		SDL_SetRenderDrawColor(renderer, 204, 0, 102, 255);
		SDL_RenderFillRect(renderer, &Progrees_Bar);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void ImageSort::getNewImage() {
	if (this->imageSurface != NULL) {
		SDL_DestroySurface(this->imageSurface);
		this->imageSurface = NULL;
	}
	if (this->imageTexture != NULL) {
		SDL_DestroyTexture(this->imageTexture);
		this->imageTexture = NULL;
	}
	seen.insert(IMGPath);
	if (seen.size() < IMGLib_size) {
		while (seen.find(IMGPath) != seen.end()) {
			IMGPath = IMGLib.getRandomImage();
		}
	} else {
		std::cout << "ALL IMAGES SEEN" << std::endl;
		exit(0);
	}
	imageSurface = IMG_Load(IMGPath.c_str());
	imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	target.w = imageSurface->w;
	target.h = imageSurface->h;
	SDL_SetWindowSize(window, target.w, target.h+50);
}