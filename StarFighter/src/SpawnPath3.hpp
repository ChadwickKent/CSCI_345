#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Game.hpp"

using namespace std;

void enemyMovement3(Sprite *A, int i, int spawning, int dir, int step) {
	if (spawning < 330) { //spawn path
		if (i < 8) {
			if (i < 4) {
				if (spawning < 0) {
					A->posX = 239; //closest 40p off screen
					A->posY = 360;
				} else if (spawning > 0 + (i * 6) && spawning < 90 + (i * 6)) {
					A->posX += 4;
					A->posY -= 2;
				} else if (spawning > 0 + (i * 6) && spawning < 160 + (i * 6)) {
					if (A->posX > ((325 + (i * 40)) - 6) && A->posX < ((325 + (i * 40)) + 6))
						A->posX = 325 + (i * 40);
					else
						A->posX -= 4;
					if (A->posY > 70)
						A->posY -= 2;
					else
						A->posY = 70;
				}
			} else {
				if (spawning < 0) {
					A->posX = 700; //closest 40p off screen
					A->posY = 360;
				} else if (spawning > 0 + ((7 - i) * 6) && spawning < 90 + ((7 - i) * 6)) {
					A->posX -= 4;
					A->posY -= 2;
				} else if (spawning > 0 + ((7 - i) * 6) && spawning < 160 + ((7 - i) * 6)) {
					if (A->posX > ((325 + (i * 40)) - 6) && A->posX < ((325 + (i * 40)) + 6))
						A->posX = 325 + (i * 40);
					else
						A->posX += 4;
					if (A->posY > 70)
						A->posY -= 2;
					else
						A->posY = 70;
				}
			}
		}
		if (i < 16 && i > 7) {
			if (i < 12) {
				if (spawning < 0) {
					A->posX = 239; //closest 30p off screen
					A->posY = 400;
				} else if (spawning > 60 + ((i - 8) * 6) && spawning < 150 + ((i - 8) * 6)) {
					A->posX += 4;
					A->posY -= 2;
				} else if (spawning > 60 + ((i - 8) * 6) && spawning < 220 + ((i - 8) * 6)) {
					if (A->posX > ((325 + ((i - 8) * 40)) - 6) && A->posX < ((325 + ((i - 8) * 40)) + 6))
						A->posX = 325 + ((i - 8) * 40);
					else
						A->posX -= 4;
					if (A->posY > 112)
						A->posY -= 2;
					else
						A->posY = 112;
				}
			} else {
				if (spawning < 0) {
					A->posX = 700; //closest 30p off screen
					A->posY = 400;
				} else if (spawning > 60 + ((15 - i) * 6) && spawning < 150 + ((15 - i) * 6)) {
					A->posX -= 4;
					A->posY -= 2;
				} else if (spawning > 60 + ((15 - i) * 6) && spawning < 220 + ((15 - i) * 6)) {
					if (A->posX > ((325 + ((i - 8) * 40)) - 6) && A->posX < ((325 + ((i - 8) * 40)) + 6))
						A->posX = 325 + ((i - 8) * 40);
					else
						A->posX += 4;
					if (A->posY > 112)
						A->posY -= 2;
					else
						A->posY = 112;
				}
			}
		}
		if (i < 24 && i > 15) {
			if (i < 20)	{
				if (spawning < 0) {
					A->posX = 239; //closest 30p off screen
					A->posY = 440;
				} else if (spawning > 120 + ((i - 16) * 6) && spawning < 210 + ((i - 16) * 6)) {
					A->posX += 4;
					A->posY -= 2;
				} else if (spawning > 120 + ((i - 16) * 6) && spawning < 280 + ((i - 16) * 6)) {
					if (A->posX > ((325 + ((i - 16) * 40)) - 6) && A->posX < ((325 + ((i - 16) * 40)) + 6))
						A->posX = 325 + ((i - 16) * 40);
					else
						A->posX -= 4;
					if (A->posY > 154)
						A->posY -= 2;
					else
						A->posY = 154;
				}
			} else {
				if (spawning < 0) {
					A->posX = 700; //closest 30p off screen
					A->posY = 440;
				} else if (spawning > 120 + ((23 - i) * 6) && spawning < 210 + ((23 - i) * 6)) {
					A->posX -= 4;
					A->posY -= 2;
				} else if (spawning > 120 + ((23 - i) * 6) && spawning < 280 + ((23 - i) * 6)) {
					if (A->posX > ((325 + ((i - 16) * 40)) - 6) && A->posX < ((325 + ((i - 16) * 40)) + 6))
						A->posX = 325 + ((i - 16) * 40);
					else
						A->posX += 4;
					if (A->posY > 154)
						A->posY -= 2;
					else
						A->posY = 154;
				}
			}
		} //return coordinates 325 + ((i * 40) - (320 * (i / 8))), 70 + (42 * (i / 8))
	} else {
		if (!(step % 3))
			A->posX += 1 * dir;
	}
};
