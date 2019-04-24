#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Game.hpp"

using namespace std;

class Image {
	SDL_Texture *texture;
	int XPos;
	int YPos;
	protected:
		SDL_Rect src;
	public:
		Image(Game *game, string filename) {
			SDL_Surface *surface;
			surface = SDL_LoadBMP(filename.c_str());
			if(surface == NULL) {
				cout << "ERROR: Loading Image" << endl;
				return;
			}
			Uint32 colorKey = SDL_MapRGB(surface->format, 0, 0xFF, 0);
			SDL_SetColorKey(surface, SDL_TRUE, colorKey);
			SDL_Renderer *renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			if(texture == NULL) {
				cout << "ERROR: Loading Image" << endl;
				return;
			}
			SDL_QueryTexture(texture, NULL, NULL, &(src.w), &(src.h));
			src.x = 0;
			src.y = 0;
			SDL_FreeSurface(surface);
		}
		SDL_Rect getSize() {
			return src;
		}
		int getX() {
			return XPos;
		}
		int getY() {
			return YPos;
		}
		void render(Game *game, int x = 0, int y = 0) {
			SDL_Rect dest;
			dest.w = src.w;
			dest.h = src.h;
			dest.x = x;
			dest.y = y;
			XPos = x;
			YPos = y;
			SDL_Renderer *renderer= game->getRenderer();
			SDL_RenderCopy(renderer, texture, &src, &dest);
		}
};
