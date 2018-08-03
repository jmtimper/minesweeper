#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

//screen variables
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

int main(int argc, char* argv[]) {

	SDL_Window *window;                    // Declare a pointer

	SDL_Event event;
	bool quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);         // Initialize SDL2
	IMG_Init(IMG_INIT_PNG);				   // Initialize PNG

										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"Minesweeper++",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		SCREEN_WIDTH,                      // width, in pixels
		SCREEN_HEIGHT,                     // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	/**
	SDL_Surface * image = IMG_Load(R"(..\..\..\..\..\Desktop\sprites.png)");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);
	*/

	SDL_Texture* spriteSheet = NULL;
	SDL_Surface * temp = IMG_Load(R"(..\..\..\..\..\Desktop\sprites.png)");
	spriteSheet = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	SDL_Rect windowRect;
	windowRect.x = 250;
	windowRect.y = 0;
	windowRect.w = 100;
	windowRect.h = 100;

	SDL_Rect textureRect;
	textureRect.x = 0;
	textureRect.y = 0;
	textureRect.w = 100;
	textureRect.h = 100;

	//SDL_QueryTexture() method gets the width and height of the texture
	SDL_QueryTexture(spriteSheet, NULL, NULL, &textureRect.w, &textureRect.h);
	//Now, textureRect.w and textureRect.h are filled
	//with respective dimensions of the image/texture

	//As there are 8 frames with same width, we simply
	//get the width of a frame by dividing with 8
	textureRect.w /= 8;

	while (!quit) {
		
		SDL_PollEvent(&event);

		switch (event.type) {

			case SDL_QUIT:
				quit = true;
				break;
		}

		//Total number of frames of the animation
		int totalFrames = 8;

		//Amount of delay in milliseconds for each frame
		int delayPerFrame = 1000;

		//SDL_GetTicks() method gives us the time in milliseconds

		//'frame' will give us the index of frame we want to render
		//For example, if 'frame' is 2, it will give us the third frame
		int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;

		//The index of frame is multiplied by the width of the frame
		//This will give us the appropriate
		//frame dimensions from the sprite sheet
		textureRect.x = frame * textureRect.w;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, spriteSheet, &textureRect, &windowRect);
		SDL_RenderPresent(renderer);
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_DestroyTexture(spriteSheet);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
