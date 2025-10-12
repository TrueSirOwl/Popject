#include "ImageSort.hpp"
#include "ImageStorage.hpp"

ImageSort::ImageSort(/* args */) {
	// open window
	// window has buttons
	// window has random image
}

ImageSort::~ImageSort() {
}


void content_sorting_routine(Settings* Sett) {
	ImageStorage IMGLib = ImageStorage(Sett->ImageFolderPath);
	LOG(INFO, Sett->LoggingStrenght , "Getting Images from : "+ Sett->ImageFolderPath);
	
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_CreateWindowAndRenderer("Content_sorting",1000, 900, 0, &window,&renderer);
	
	//SDL_SetRenderVSync(renderer, 1);
	
	SDL_Event event;

	SDL_FRect target;
	target.w = 1000;
	target.h = 850;
	target.x = 0;
	target.y = 0;
	
	SDL_FRect Keep_Button;
	SDL_FRect Delete_Button;
	
	std::unordered_set<std::string> seen;

	std::string IMGPath = IMGLib.getRandomImage();
	SDL_Surface* imageSurface = IMG_Load(IMGPath.c_str());
	target.w = imageSurface->w;
	target.h = imageSurface->h;
	SDL_SetWindowSize(window, target.w, target.h+50);
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_SetWindowResizable(window, true);
	SDL_SetWindowAlwaysOnTop(window,true);

	int wx = 0;
	int wy = 0;

	int mousex = 0;
	int mousey = 0;

	bool running = true;


	while (running == true) {
		SDL_Delay(1);
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_MOUSE_BUTTON_DOWN:

				SDL_GetWindowSize(window, &wx, &wy);
				mousex = event.button.x;
				mousey = event.button.y;
				if (mousey > wy-50 && mousex >= wx/2) {
					seen.insert(IMGPath);
					while (seen.find(IMGPath) != seen.end()) {
						IMGPath = IMGLib.getRandomImage();
					}
					imageSurface = IMG_Load(IMGPath.c_str());
					imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
					target.w = imageSurface->w;
					target.h = imageSurface->h;
					SDL_SetWindowSize(window, target.w, target.h+50);
				}
				if (mousey > wy-50 && mousex < wx/2) {
					std::string filename = IMGPath.substr(IMGPath.find_last_of('/'));
					std::filesystem::copy_file(IMGPath, Sett->TrashbinPath + filename);
					std::filesystem::remove(IMGPath);
					seen.insert(IMGPath);
					while (seen.find(IMGPath) != seen.end()) {
						IMGPath = IMGLib.getRandomImage();
					}
					imageSurface = IMG_Load(IMGPath.c_str());
					imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
					target.w = imageSurface->w;
					target.h = imageSurface->h;
					SDL_SetWindowSize(window, target.w, target.h+50);
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
		Keep_Button.x = w/2;
		Keep_Button.y = h-50;
		Keep_Button.w = w/2;
		Keep_Button.h = 50;
		Delete_Button.x = 0;
		Delete_Button.y = h-50;
		Delete_Button.w = w/2;
		Delete_Button.h = 50;
		SDL_RenderTexture(renderer, imageTexture, NULL, &target);
		SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
		SDL_RenderFillRect(renderer, &Keep_Button);
		SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
		SDL_RenderFillRect(renderer, &Delete_Button);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}