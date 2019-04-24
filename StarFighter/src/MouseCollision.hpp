#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Game.hpp"

using namespace std;

bool mouseCollision(Image *button, SDL_Event event) { // Checks if Mouse is over the Button -Joey
	int x, y;
	int ins = true;
	SDL_GetMouseState(&x, &y);
	if (x < button->getX()){
		ins = false;
	} else if (x > button->getX() + button->getSize().w) {
		ins = false;
	} else if (y < button->getY()) {
		ins = false;
	} else if (y > button->getY() + button->getSize().h) {
		ins = false;
	}
	return ins;
};
