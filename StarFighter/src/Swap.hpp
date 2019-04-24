#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Game.hpp"

using namespace std;

void swap(SDL_Event event, SDL_Keycode key, int num,vector <Sprite *> ship, Sprite *player, Sprite *temp) {
	if(event.key.keysym.sym == key && ship[num]->active == false && ship[num]->alive == true) {
		player->weapon = ship[num]->weapon;
		for(int i = 0; i < 3; i++)
			if(ship[i]->active == true) {
				ship[i]->posX = temp->posX;
				ship[i]->posY = temp->posY;
				ship[i]->active = false;
			}
		ship[num]->active = true;
		temp->posX = ship[num]->posX;
		temp->posY = ship[num]->posY;
		ship[num]->posY = player->posY;
		}
};
