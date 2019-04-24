#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Game.hpp"

using namespace std;

class Sprite {
	SDL_Texture *texture;
	protected:
		SDL_Rect src;
	public:
		int posX = 0;
		int posY = 0;
		int w = 0;
		int h = 0;
		bool alive = true;
		bool active = false;
		int weapon = 0;
		Sprite(Game *game, string filename, int newX, int newY) {
			posX = newX;
			posY = newY;
			
			SDL_Surface *surface;
			surface = SDL_LoadBMP(filename.c_str());
			if(surface == NULL) {
				cout << "ERROR: Loading Sprite for Surface" << endl;
				return;
			}
			
			Uint32 colorKey = SDL_MapRGB(surface->format, 0, 0xFF, 0);
			SDL_SetColorKey(surface, SDL_TRUE, colorKey);
			SDL_Renderer *renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			if(texture == NULL) {
				cout << "ERROR: Loading Sprite for Texture" << endl;
				return;
			}
			SDL_QueryTexture(texture, NULL, NULL, &(src.w), &(src.h));
			src.x = 0;
			src.y = 0;
			SDL_FreeSurface(surface);
			w = src.w;
			h = src.h;
		}
		SDL_Rect getSize() {
			return src;
		}
		void render(Game *game, int x, int y) {
			SDL_Rect dest;
			dest.w = src.w;
			dest.h = src.h;
			dest.x = x;
			dest.y = y;
			SDL_Renderer *renderer= game->getRenderer();
			SDL_RenderCopy(renderer, texture, &src, &dest);
		}
};
