#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Game.hpp"

using namespace std;

int collision(Sprite *A, Sprite *B){
	if(A->posX > B->posX && A->posX < (B->posX + B->w) && A->posY > B->posY && A->posY < (B->posY + B->h)) {
		A->alive = false;
		B->alive = false;
	}
	if((A->posX + A->w) > B->posX && (A->posX + A->w) < (B->posX + B->w) && A->posY > B->posY && A->posY < (B->posY + B->h)) {
		A->alive = false;
		B->alive = false;
	}
	if(A->posX > B->posX && A->posX < (B->posX + B->w) && (A->posY + A->h) > B->posY && (A->posY + A->h) < (B->posY + B->h)) {
		A->alive = false;
		B->alive = false;
	}
	if((A->posX + A->w) > B->posX && (A->posX + A->w) < (B->posX + B->w) && (A->posY + A->h) > B->posY && (A->posY + A->h) < (B->posY + B->h)) {
		A->alive = false;
		B->alive = false;
	}
	if(A->posX < B->posX && (A->posX + A->w) > (B->posX + B->w) && A->posY > B->posY && (A->posY + A->h) < (B->posY + B->h)) {
		A->alive = false;
		B->alive = false;
	}
	if(B->alive == false)
		return 250;
	else
		return 0;
};
