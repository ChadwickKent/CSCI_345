#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Game { 
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Rect size;
	public:
		Game(string name, int w = 960, int h = 540) {
			srand(time(NULL));
			size.w = w;
			size.h = h;
			window = NULL;
			renderer = NULL;
			SDL_Init(SDL_INIT_EVERYTHING);
			window = SDL_CreateWindow(
				name.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				w,
				h,
				SDL_WINDOW_OPENGL
			);
			if(window == NULL) {
				cout << "ERROR: Creating Window > " <<  SDL_GetError() << endl;
				return;
			}
			renderer = SDL_CreateRenderer(window, -1, 0);
			if(renderer == NULL) {
				cout << "ERROR: Ceating Renderer > " << SDL_GetError() << endl;
				return;
			}
		}
		SDL_Rect getSize() { return size; }
		SDL_Renderer *getRenderer() { return renderer;}
		SDL_Window *getWindow() { return window; }
		~Game(){
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
	virtual void init() = 0;
	virtual void loop() = 0;
	void run() { 
		if(renderer == NULL || window == NULL) return;
		init();
		loop();
	}
};
