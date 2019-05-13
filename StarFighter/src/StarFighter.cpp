#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_mixer.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <sstream>
#include <time.h>
#include "Game.hpp"
#include "Image.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "MouseCollision.hpp"
#include "Swap.hpp"
#include "SpawnPath1.hpp"
#include "SpawnPath2.hpp"
#include "SpawnPath3.hpp"

using namespace std;

class NewGame:public Game {
	string file = "../include/";
	Mix_Music *music = NULL;
	Mix_Chunk *rocketS = NULL;
	Mix_Chunk *pulseS = NULL;
	Mix_Chunk *beamS = NULL;
	Mix_Chunk *collisionS = NULL;
	Mix_Chunk *selectS = NULL;
	Image *background;
	Image *title;
	Image *optionsMenu;
	Image *controlsMenu;
	Image *playButton;
	Image *trainingButton;
	Image *optionsButton;
	Image *controlsButton;
	Image *pauseButton;
	Image *xButton;
	Image *speakerButton;
	Image *muteButton;
	Image *gameoverButton;
	Image *upMusicButton;
	Image *downMusicButton;
	Image *upSFXButton;
	Image *downSFXButton;
	Image *edgeR;
	Image *edgeL;
	Image *screen;
	vector<Image *> musicLight;
	vector<Image *> sfxLight;
	vector<Image *> scoreboard;
	vector<Image *> waveCount;
	vector<Image *> energy;
	vector<Image *> energy2;
	Sprite *player;
	Sprite *temp;
	vector<Sprite *> ship;
	vector<Sprite *> rockets;
	int rAmmo = 3;
	vector<Sprite *> sPulse;
	int pAmmo = 2;
	Sprite *beam;
	vector<Sprite *> grunt;
	int troops = 24;
	vector<Sprite *> gPulse;
	
	public:
		NewGame():Game("StarFighter", 960, 540){}
		void init() {
			Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
			music = Mix_LoadMUS("../include/audio/bgm.wav");
			Mix_VolumeMusic(14);
			rocketS = Mix_LoadWAV("../include/audio/rocket.wav");
			Mix_VolumeChunk(rocketS, 10);
			pulseS = Mix_LoadWAV("../include/audio/pulse.wav");
			Mix_VolumeChunk(pulseS, 10);
			beamS = Mix_LoadWAV("../include/audio/beam.wav");
			Mix_VolumeChunk(beamS, 10);
			collisionS = Mix_LoadWAV("../include/audio/collision.wav");
			Mix_VolumeChunk(collisionS, 10);
			selectS = Mix_LoadWAV("../include/audio/select.wav");
			Mix_VolumeChunk(selectS, 10);
			background = new Image(this, file + "bgd.bmp");
			title = new Image(this, file + "title.bmp");
			optionsMenu = new Image(this, file + "optionsMenu.bmp");
			controlsMenu = new Image(this, file + "controlsMenu.bmp");
			playButton = new Image(this, file + "playButton.bmp");
			trainingButton = new Image(this, file + "trainingButton.bmp");
			optionsButton = new Image(this, file + "optionsButton.bmp");
			controlsButton = new Image(this, file + "controlsButton.bmp");
			pauseButton = new Image(this, file + "pauseButton.bmp");
			xButton = new Image(this, file + "xButton.bmp");
			speakerButton = new Image(this, file + "speakerButton.bmp");
			muteButton = new Image(this, file + "muteButton.bmp");
			gameoverButton = new Image(this, file + "gameoverButton.bmp");
			upMusicButton = new Image(this, file + "upArrowButton.bmp");
			downMusicButton = new Image(this, file + "downArrowButton.bmp");
			upSFXButton = new Image(this, file + "upArrowButton.bmp");
			downSFXButton = new Image(this, file + "downArrowButton.bmp");
			edgeR = new Image(this, file + "frameR.bmp");
			edgeL = new Image(this, file + "frameL.bmp");
			screen = new Image(this, file + "screen.bmp");
			for (int i = 0; i < 10; i++) {
				Image *light = new Image(this, file + "light.bmp");
				musicLight.push_back(light);
				Image *light2 = new Image(this, file + "light.bmp");
				sfxLight.push_back(light2);
			}
			int count = 0;
			for (int i = 0; i < 60; i++) {
				Image *digit = new Image(this, file + "score/" + to_string(count) + ".bmp");
				scoreboard.push_back(digit);
				count++;
				if(count > 9)
					count = 0;
			}
			count = 0;
			for (int i = 0; i < 20; i++) {
				Image *waveDigit = new Image(this, file + "text/" + to_string(count) + ".bmp");
				waveCount.push_back(waveDigit);
				count++;
				if(count > 9)
					count = 0;
			}
			for (int i = 0; i < 10; i++) {
				 // rocket weapon
				Sprite *rocket = new Sprite(this, file + "rocket.bmp", 181 - (i * 9), 351);
				rockets.push_back(rocket);
				 // pulse weapon
				Sprite *pulse2 = new Sprite(this, file + "pulse2.bmp", 181 - (i * 9), 351);
				sPulse.push_back(pulse2);
				 // beam weapon
				Image *e = new Image(this, file + "energy.bmp");
				energy.push_back(e);
				Image *e2 = new Image(this, file + "energy2.bmp");
				energy2.push_back(e2);
			}
			beam = new Sprite(this, file + "beam.bmp", -10, 0);
			player = new Sprite(this, file + "non0.bmp", 465, 440); // non0 is a empty texture to give a hit box (i want this to change -chad)
			temp = new Sprite(this, file + "non0.bmp", 0, 0);
			for (int i = 0; i < 3; i++) {
				Sprite *vehicle = new Sprite(this, file + "ship" + to_string(i + 1) + ".bmp", 78 + (47 * i), 401);
				ship.push_back(vehicle); 
			}
			for (int i = 0; i < troops; i++) {
				Sprite *enemy = new Sprite(this, file + "grunt.bmp", 325 + ((i * 40) - (320 * (i / 8))), -230 + (42 * (i / 8)));
				grunt.push_back(enemy);
				Sprite *pulse = new Sprite(this, file + "pulse.bmp", grunt[i]->posX, grunt[i]->posY);
				gPulse.push_back(pulse);
			}
		}
		
		Mix_FreeMusic(Mix_Music music);
		
		void loop() {
			SDL_Event event;
			unsigned start = SDL_GetTicks();
			bool running = true;
			bool reset = false;
			bool godmode = false;
			bool muted = false;
			int volumeMusic = 5;
			int volumeSFX = 5;
			int volumeMute = 0;
			string room = "title";
			int step = -30;			//ticks
			int screenScroll = 0;
			int dir = 1;			//direction
			int offset = 0;
			int score = 0;
			int dig = 0;			//digit
			int board = 0;
			int respawn = 30;
			int charge = 10;
			int phase = 0;
			int spawning = 0;
			int wave = 1;
			int hero = 24;			//active enemy ship
			int gameOver = 0;
			int coolDown = 0;
			
			//initialize weapon testing
			for(int i = 0; i < 3; i++)
				ship[i]->weapon = i;
				// 0 = rockets  1 = pulse  2 = beam
				
			//initializes player to be red ship
			ship[0]->active = true;
			player->weapon = ship[0]->weapon;
			temp->posX = ship[0]->posX;
			temp->posY = ship[0]->posY;	
			ship[0]->posY = player->posY;
			
			
			while(running) {
				if(coolDown > 0)
					coolDown--;
				if(SDL_PollEvent(&event))
					if(event.type == SDL_QUIT)
						running = false;
					if(event.type == SDL_KEYDOWN) {
						if(event.key.keysym.sym == SDLK_p)
							if(room == "level" || room == "pause") {
								if(room == "level")
									room = "pause";
								else
									room = "level";
							}
						if(event.key.keysym.sym == SDLK_ESCAPE) //quits
							running = false;
						if(room == "level") {
							if(player->weapon == 0)
								if(event.key.keysym.sym == SDLK_SPACE) {
									bool fired = false;
									for (int i = rAmmo - 1; i > -1; i--)
										if(rockets[i]->alive == true && rockets[i]->active == false)
											if(fired == false) {
												rockets[i]->posX = player->posX + 15;
												rockets[i]->posY = player->posY + 3;
												rockets[i]->active = true;
												fired = true;
												Mix_PlayChannel( -1, rocketS, 0 );
											}
								}
							if(player->weapon == 1)
								if(event.key.keysym.sym == SDLK_SPACE) {
									bool fired = false;
									for (int i = pAmmo - 1; i > -1; i--)
										if(sPulse[i]->alive == true && sPulse[i]->active == false)
											if(fired == false) {
												sPulse[i]->posX = player->posX + 15;
												sPulse[i]->posY = player->posY + 3;
												sPulse[i]->active = true;
												fired = true;
												Mix_PlayChannel( -1, pulseS, 0 );
											}
								}
							if(player->weapon == 2)
								if(event.key.keysym.sym == SDLK_SPACE && charge > 9) {
									beam->posY = player->posY - 540;
									beam->active = true;
									charge = 0;
									phase = 0;
									Mix_PlayChannel( -1, beamS, 0 );
								}
							swap(event, SDLK_q, 0, ship, player, temp);
							swap(event, SDLK_w, 1, ship, player, temp);
							swap(event, SDLK_e, 2, ship, player, temp);
							if(event.key.keysym.sym == SDLK_k)//kill command
								for(int i = 0; i < 3; i++)
									if(ship[i]->active == true)
										ship[i]->alive = false;
							if(event.key.keysym.sym == SDLK_g) { //godmode cheat
								if(godmode == false)
									godmode = true;
								else
									godmode = false;
							}
						}
						else if(room == "test") {
							rAmmo = 10; //FULL AMMO
							pAmmo = 10; //
							if(player->weapon == 0)
								if(event.key.keysym.sym == SDLK_SPACE) {
									bool fired = false;
									for (int i = rAmmo - 1; i > -1; i--)
										if(rockets[i]->alive == true && rockets[i]->active == false)
											if(fired == false) {
												rockets[i]->posX = player->posX + 15;
												rockets[i]->posY = player->posY + 3;
												rockets[i]->active = true;
												fired = true;
												Mix_PlayChannel( -1, rocketS, 0 );
											}
								}
							if(player->weapon == 1)
								if(event.key.keysym.sym == SDLK_SPACE) {
									bool fired = false;
									for (int i = pAmmo - 1; i > -1; i--)
										if(sPulse[i]->alive == true && sPulse[i]->active == false)
											if(fired == false) {
												sPulse[i]->posX = player->posX + 15;
												sPulse[i]->posY = player->posY + 3;
												sPulse[i]->active = true;
												fired = true;
												Mix_PlayChannel( -1, pulseS, 0 );
											}
								}
							if(player->weapon == 2)
								if(event.key.keysym.sym == SDLK_SPACE && charge > 9) {
									beam->posY = player->posY - 540;
									beam->active = true;
									charge = 0;
									phase = 0;
									Mix_PlayChannel( -1, beamS, 0 );
								}
							swap(event, SDLK_q, 0, ship, player, temp);
							swap(event, SDLK_w, 1, ship, player, temp);
							swap(event, SDLK_e, 2, ship, player, temp);
						}
					}
					
				// Button Mouse Event
				if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
					if (mouseCollision(playButton, event) && room == "title")
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
								room = "level";
								Mix_PlayChannel( -1, selectS, 0 );
								spawning = -30;
								player->posX = 465;
								for(int i = 0; i < 10; i++) {
									rockets[i]->alive = false;
									sPulse[i]->alive = false;
								}
								for (int i = 0; i < troops; i++) {
									grunt[i]->alive = true;
									gPulse[i]->alive = false;
								}
								for(int i = 0; i < 3; i++) {
									ship[i]->alive = true;
									if(ship[i]->active == true) {
										ship[i]->active = false;
										ship[i]->posX = temp->posX;
										ship[i]->posY = temp->posY;
									}
								}
								ship[0]->active = true;
								player->weapon = ship[0]->weapon;
								temp->posX = ship[0]->posX;
								temp->posY = ship[0]->posY;
								ship[0]->posX = player->posX;
								ship[0]->posY = player->posY;
								hero = 24;
								step = 0;
								charge = 10;
								phase = 0;
								score = 0;
								rAmmo = 3;
								pAmmo = 2;
						}
					if (mouseCollision(trainingButton, event) && room == "title")
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							room = "test";
							Mix_PlayChannel( -1, selectS, 0 );
							spawning = 0;
							player->posX = 465;
							for(int i = 0; i < 10; i++) {
								rockets[i]->alive = false;
								sPulse[i]->alive = false;
							}
							for (int i = 0; i < troops; i++) {
								grunt[i]->alive = true;
								gPulse[i]->alive = false;
							}
							for(int i = 0; i < 3; i++) {
								ship[i]->alive = true;
								if(ship[i]->active == true) {
									ship[i]->active = false;
									ship[i]->posX = temp->posX;
									ship[i]->posY = temp->posY;
								}
							}
							ship[0]->active = true;
							player->weapon = ship[0]->weapon;
							temp->posX = ship[0]->posX;
							temp->posY = ship[0]->posY;
							ship[0]->posX = player->posX;
							ship[0]->posY = player->posY;
							hero = 24;
							step = 0;
							charge = 10;
							phase = 0;
							score = 0;
						}
					if (mouseCollision(optionsButton, event) && room == "title")
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							room = "option";
							Mix_PlayChannel( -1, selectS, 0 );
						}
					if (mouseCollision(downMusicButton, event) && room == "option" && coolDown == 0)
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							if(volumeMusic >= 1)
								volumeMusic--;
							coolDown = 9;
							Mix_PlayChannel( -1, selectS, 0 );
						}
					if (mouseCollision(upMusicButton, event) && room == "option" && coolDown == 0)
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							if(volumeMusic <= 9)
								volumeMusic++;
							coolDown = 9;
							Mix_PlayChannel( -1, selectS, 0 );
						}
					if (mouseCollision(downSFXButton, event) && room == "option" && coolDown == 0)
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							if(volumeSFX >= 1)
								volumeSFX--;
							coolDown = 9;
							Mix_PlayChannel( -1, selectS, 0 );
						}
					if (mouseCollision(upSFXButton, event) && room == "option" && coolDown == 0)
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							if(volumeSFX <= 9)
								volumeSFX++;
							coolDown = 9;
							Mix_PlayChannel( -1, selectS, 0 );
						}
					if (mouseCollision(controlsButton, event) && room == "title")
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							room = "control";
							Mix_PlayChannel( -1, selectS, 0 );
						}
					if (mouseCollision(speakerButton, event) && muted == false && coolDown == 0)
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							muted = true;
							Mix_PlayChannel( -1, selectS, 0 );
							coolDown = 9;
						}
					if (mouseCollision(muteButton, event) && muted == true && coolDown == 0)
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							muted = false;
							Mix_PlayChannel( -1, selectS, 0 );
							coolDown = 9;
						}
					if (mouseCollision(xButton, event) && room != "title")
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							room = "title";
							Mix_PlayChannel( -1, selectS, 0 );
							gameOver = 0;
							wave = 1;
						}
				}
				
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if(room == "level" || room == "test") {
					if(currentKeyStates[SDL_SCANCODE_RIGHT])
						if(player->posX < 619)
							player->posX += 5;
					if(currentKeyStates[SDL_SCANCODE_LEFT])
						if(player->posX > 310)
							player->posX -= 5;
				}
				SDL_Renderer *renderer = getRenderer();
				
				//bgm
				if( Mix_PlayingMusic() == 0 )
					Mix_PlayMusic( music, -1);
					
				//check volume
				if(muted == true) {
					Mix_VolumeMusic(0);
					Mix_VolumeChunk(rocketS, 0);
					Mix_VolumeChunk(pulseS, 0);
					Mix_VolumeChunk(beamS, 0);
					Mix_VolumeChunk(collisionS, 0);
					Mix_VolumeChunk(selectS, 0);
				} else {
					Mix_VolumeMusic(volumeMusic * 2);
					Mix_VolumeChunk(rocketS, (volumeSFX * 1));
					Mix_VolumeChunk(pulseS, (volumeSFX * 1));
					Mix_VolumeChunk(beamS, (volumeSFX * 1));
					Mix_VolumeChunk(collisionS, (volumeSFX * 2));
					Mix_VolumeChunk(selectS, (volumeSFX * 4));
				}
				
				if(room == "title") {
					background->render(this);
					title->render(this, 259, 112);
					playButton->render(this, 399, 260);
					trainingButton->render(this, 399, 320);
					optionsButton->render(this, 399, 362);
					controlsButton->render(this, 399, 404);
					if (muted == true)
						muteButton->render(this, 60, 20);
					else
						speakerButton->render(this, 60, 20);
				} else if(room == "option") {
					optionsMenu->render(this);
					xButton->render(this, 20, 20);
					if (muted == true)
						muteButton->render(this, 60, 20);
					else
						speakerButton->render(this, 60, 20);
					upMusicButton->render(this, 696, 235);
					downMusicButton->render(this, 234, 235);
					upSFXButton->render(this, 696, 374);
					downSFXButton->render(this, 234, 374);
					for(int i = 0; i < 10; i++) {
						if (i <= (volumeMusic - 1))
							musicLight[i]->render(this, 278 + (i * 42), 238);
						if (i <= (volumeSFX - 1))
							sfxLight[i]->render(this, 278 + (i * 42), 377);
					}
				} else if(room == "control") {
					controlsMenu->render(this);
					xButton->render(this, 20, 20);
					if (muted == true)
						muteButton->render(this, 60, 20);
					else
						speakerButton->render(this, 60, 20);
				} else if(room == "level") {
					if(!(step % 60)) //enemy drift
						dir *= 1;
					else if(!(step % 30))
						dir *= -1;
					if(!(step % 146)) { //active enemy event
						if(hero < 24) {
							grunt[hero]->posX = (325 + ((hero * 40) - (320 * (hero / 8)))) + offset; //return
							grunt[hero]->posY = 70 + (42 * (hero / 8));
						}
						if(spawning > 360) {
							for(int i = 0; i < 30; i++) {
								hero = rand() % 24; //new active enemy
								if(grunt[hero]->alive == true)
									break;
							}
						} else
							hero = 24;
					}
					if(!(step % 50)) { //rocket respawn
						for(int i = 0; i < rAmmo; i++) {
							if(rockets[i]->alive == false){
								rockets[i]->alive = true;
								rockets[i]->active = false;
								rockets[i]->posX = 181 - (i * 9);
								rockets[i]->posY = 351;
								break;
							}
						}
						for(int i = 0; i < pAmmo; i++) {
							if(sPulse[i]->alive == false){
								sPulse[i]->alive = true;
								sPulse[i]->active = false;
								sPulse[i]->posX = 181 - (i * 9);
								sPulse[i]->posY = 351;
								break;
							}
						}
					}
					if(!(step % 35))
						if(charge < 10)
							charge++;
					if(phase > 5)
						beam->active = false;
					if(hero < 24)
						if(grunt[hero]->alive == true) { //active enemy path
							grunt[hero]->posY += 4;
							if(grunt[hero]->posY > 540)
								grunt[hero]->posY = -42;
							if(grunt[hero]->posY > 200 && grunt[hero]->posY < 390) {
								if(grunt[hero]->posX < player->posX && grunt[hero]->posX < (player->posX + 10))
									grunt[hero]->posX += 4;
								else if(grunt[hero]->posX > player->posX && grunt[hero]->posX > (player->posX + 10) )
									grunt[hero]->posX -= 4;
								if(grunt[hero]->posX >= player->posX && grunt[hero]->posX <= (player->posX + 10))
									if(gPulse[hero]->active == false) {
										gPulse[hero]->posX = grunt[hero]->posX + 10;
										gPulse[hero]->posY = grunt[hero]->posY + 10;
										gPulse[hero]->active = true;
										Mix_PlayChannel( -1, pulseS, 0 );
									}
							}
							if(grunt[hero]->posY < (70 + (42 * (hero / 8))) || grunt[hero]->posY > 480) {
								if(grunt[hero]->posX < ((325 + ((hero * 40) - (320 * (hero / 8)))) + offset))
									grunt[hero]->posX += 4;
								else if(grunt[hero]->posX > ((325 + ((hero * 40) - (320 * (hero / 8)))) + offset))
									grunt[hero]->posX -= 4;
								if(grunt[hero]->posX > ((325 + ((hero * 40) - (320 * (hero / 8)))) + offset - 6) && grunt[hero]->posX < ((325 + ((hero * 40) - (320 * (hero / 8)))) + offset + 6))
									grunt[hero]->posX = (325 + ((hero * 40) - (320 * (hero / 8)))) + offset;
							}
						} //end of path
						if(hero < 24) {
							if(gPulse[hero]->alive == true)
								if(gPulse[hero]->active == false) {
									gPulse[hero]->posX = 10;
									gPulse[hero]->posY = 10;
								} else
									gPulse[hero]->posY += 6;
							if(gPulse[hero]->posY > 540)
								gPulse[hero]->active = false;
							if(gPulse[hero]->alive == false) {
								gPulse[hero]->posX = 10;
								gPulse[hero]->posY = 10;
								gPulse[hero]->alive = true;
							}
						}
					for (int i = 0; i < troops; i++)
						if(grunt[i]->alive == true)
							if(i != hero) {
								if(!(wave % 2))
									enemyMovement2(grunt[i], i, spawning, dir, step);
								else
									enemyMovement1(grunt[i], i, spawning, dir, step);
							}
					for (int i = 0; i < rAmmo; i++) {
						if(rockets[i]->active == true)
							rockets[i]->posY -= 6;
						if(rockets[i]->posY < -10)
							rockets[i]->alive = false;
					}
					for (int i = 0; i < pAmmo; i++) {
						if(sPulse[i]->active == true)
							sPulse[i]->posY -= 10;
						if(sPulse[i]->posY < -10)
							sPulse[i]->alive = false;
					}
					if(beam->active == true)
						beam->posX = player->posX + 12;
					else
						beam->posX = -10;
					for(int i = 0; i < 3; i++)
						if(ship[i]->active == true)
							ship[i]->posX = player->posX;
					//render
					screen->render(this, 300, -540 + screenScroll);
					if(hero < 24)
						if(gPulse[hero]->alive == true)
							if(gPulse[hero]->active == true)
								gPulse[hero]->render(this, gPulse[hero]->posX, gPulse[hero]->posY);
					for (int i = 0; i < troops; i++)
						if(grunt[i]->alive == true)
							grunt[i]->render(this, grunt[i]->posX, grunt[i]->posY);
					edgeR->render(this);
					edgeL->render(this, 660);
					if(player->weapon == 0)
						for(int i = 0; i < rAmmo; i++)
							if(rockets[i]->alive == true)
								rockets[i]->render(this, rockets[i]->posX, rockets[i]->posY);
					if(player->weapon == 1)
						for(int i = 0; i < pAmmo; i++)
							if(sPulse[i]->alive == true)
								sPulse[i]->render(this, sPulse[i]->posX, sPulse[i]->posY);
					if(player->weapon == 2) {
						if(beam->active == true)
							beam->render(this, beam->posX, beam->posY);
						for(int i = 0; i < 10; i++)
							energy2[i]->render(this, 181 - (i * 9), 351);
						for(int i = 0; i < 10; i++)
							if(charge >= i + 1)
								energy[i]->render(this, 181 - (i * 9), 351);
					}
					for(int i = 0; i < rAmmo; i++)
						if(rockets[i]->active == true)
							if(rockets[i]->alive == true)
								rockets[i]->render(this, rockets[i]->posX, rockets[i]->posY);
					for(int i = 0; i < pAmmo; i++)
						if(sPulse[i]->active == true)
							if(sPulse[i]->alive == true)
								sPulse[i]->render(this, sPulse[i]->posX, sPulse[i]->posY);
					for(int i = 0; i < 3; i++)
						if(ship[i]->alive == true)
							ship[i]->render(this, ship[i]->posX, ship[i]->posY);
					board = score;
					for(int i = 0; i < 6; i++) {
						dig = 5 - i;
						scoreboard[(board % 10) + (dig * 10)]->render(this, 760 + (18 * dig), 106);		
						board /= 10;
					}
					if (spawning < 20) {
						board = wave;
						for(int i = 0; i < 2; i++) {
							dig = 1 - i;
							waveCount[(board % 10) + (dig * 10)]->render(this, 460 + (18 * dig), 106);		
							board /= 10;
						}
					}
					xButton->render(this, 20, 20);
					if (muted == true)
						muteButton->render(this, 60, 20);
					else
						speakerButton->render(this, 60, 20);
					//increment
					step++;
					spawning++;
					respawn++;
					phase++;
					if(!(step % 3))
						offset += 1 * dir;
					screenScroll++;
					if(screenScroll >= 540) //reset screen
						screenScroll = 0;
					//collision	
						//check player
					if(respawn > 30)
						if(godmode == false)
							for (int i = 0; i < 3; i++)
								if(ship[i]->active == true) {
									for (int j = 0; j < troops; j++)
										if(grunt[j]->alive == true)
											collision(grunt[j], ship[i], collisionS);
									for (int j = 0; j < troops; j++)
										if(gPulse[j]->alive == true)
											collision(gPulse[j], ship[i], collisionS);
									if(ship[i]->alive == false)
										if(gameOver > 1) {
											player->alive = false;
											room = "over";
										}
									else
										for(int k = 0; k < 3; k++)
											if(ship[k]->alive == true) {
													respawn = 0;
													ship[i]->active = false;
													player->weapon = ship[k]->weapon;
													ship[i]->posX = temp->posX;
													ship[i]->posY = temp->posY;
													ship[k]->active = true;
													temp->posX = ship[k]->posX;
													temp->posY = ship[k]->posY;
													ship[k]->posY = player->posY;
													gameOver++;
													break;
											}
								}
						//check projectile
					for (int i = 0; i < rAmmo; i++)
						if(rockets[i]->alive == true)
							if(rockets[i]->active == true) {
								for (int j = 0; j < troops; j++)
									if(grunt[j]->alive == true)
										score += collision(rockets[i], grunt[j], collisionS);
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
										if(gPulse[j]->active == true)
											collision(gPulse[j], rockets[i], collisionS);
							}
					for (int i = 0; i < pAmmo; i++)
						if(sPulse[i]->alive == true)
							if(sPulse[i]->active == true) {
								for (int j = 0; j < troops; j++)
									if(grunt[j]->alive == true)
										score += collision(sPulse[i], grunt[j], collisionS);
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
										if(gPulse[j]->active == true)
											collision(gPulse[j], sPulse[i], collisionS);
							}
					if(beam->active == true)
						if(beam->active == true) {
							for (int j = 0; j < troops; j++) {
								beam->alive = true;
								if(grunt[j]->alive == true)
									score += collision(grunt[j], beam, collisionS);
							}
							for (int j = 0; j < troops; j++)
								if(gPulse[j]->alive == true)
									if(gPulse[j]->active == true)
										collision(gPulse[j], beam, collisionS);
						}
					//wave reset
					if(!(step % 60)) {
						reset = true;
						for(int i = 0; i < troops; i++)
							if(grunt[i]->alive == true)
								reset = false;
						if(reset == true) {
							wave++;
							if(wave > 15)
								room = "over";
							else {
								for(int i = 0; i < troops; i++) {
									grunt[i]->alive = true;
									grunt[i]->posY = -70;
								}
								spawning = -30;
								hero = 24;
							}
						}
					}
				} else if(room == "test") {
					if(spawning == 0) {
						for(int i = 0; i < troops; i++) {
							grunt[i]->posX = 325 + ((i * 40) - (320 * (i / 8)));
							grunt[i]->posY = 70 + (42 * (i / 8));
						}
					}
					if(!(step % 146)) { //active enemy event
						if(hero < 24) {
							if(hero == 0) //return
								grunt[hero]->posX = grunt[1]->posX - 40;
							else
								grunt[hero]->posX = grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)));
							grunt[hero]->posY = 70 + (42 * (hero / 8));
						}
						for(int i = 0; i < 30; i++) {
							hero = rand() % 24; //new active enemy
							if(grunt[hero]->alive == true)
								break;
						}
					}
					if(!(step % 1)) { //rocket respawn //changed 50 to 1
						for(int i = 0; i < rAmmo; i++) {
							if(rockets[i]->alive == false){
								rockets[i]->alive = true;
								rockets[i]->active = false;
								rockets[i]->posX = 181 - (i * 9);
								rockets[i]->posY = 351;
								break;
							}
						}
						for(int i = 0; i < pAmmo; i++) {
							if(sPulse[i]->alive == false){
								sPulse[i]->alive = true;
								sPulse[i]->active = false;
								sPulse[i]->posX = 181 - (i * 9);
								sPulse[i]->posY = 351;
								break;
							}
						}
					}
					if(!(step % 35))
						if(charge < 10)
							charge += 50;
					if(phase > 5)
						beam->active = false;
					if(hero < 24)
						if(grunt[hero]->alive == true) { //active enemy path
							grunt[hero]->posY += 4;
							if(grunt[hero]->posY > 540)
								grunt[hero]->posY = -42;
							if(grunt[hero]->posY > 200 && grunt[hero]->posY < 390) {
								if(grunt[hero]->posX < player->posX && grunt[hero]->posX < (player->posX + 10))
									grunt[hero]->posX += 4;
								else if(grunt[hero]->posX > player->posX && grunt[hero]->posX > (player->posX + 10) )
									grunt[hero]->posX -= 4;
								if(grunt[hero]->posX >= player->posX && grunt[hero]->posX <= (player->posX + 10))
									if(gPulse[hero]->active == false) {
										gPulse[hero]->posX = grunt[hero]->posX + 10;
										gPulse[hero]->posY = grunt[hero]->posY + 10;
										gPulse[hero]->active = true;
									}
							}
							if(grunt[hero]->posY < (70 + (42 * (hero / 8))) || grunt[hero]->posY > 480) {
								if(hero == 0) {
									if(grunt[hero]->posX < (grunt[1]->posX - 40) && grunt[hero]->posX < (grunt[1]->posX - 40))
										grunt[hero]->posX += 4;
									else if(grunt[hero]->posX > (grunt[1]->posX - 40) && grunt[hero]->posX > (grunt[1]->posX - 30))
										grunt[hero]->posX -= 4;
									if(grunt[hero]->posX > (grunt[1]->posX - 40) && grunt[hero]->posX < (grunt[1]->posX - 40))
										grunt[hero]->posX = grunt[1]->posX - 40;
								} else {
									if(grunt[hero]->posX < (grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)))) && grunt[hero]->posX < (grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)))) + 10)
										grunt[hero]->posX += 4;
									else if(grunt[hero]->posX > (grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)))) && grunt[hero]->posX > (grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)))) + 10)
										grunt[hero]->posX -= 4;
									if(grunt[hero]->posX > (grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)))) && grunt[hero]->posX < (grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)))) + 10)
										grunt[hero]->posX = grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)));
								}
							}
						} //end of path
						if(gPulse[hero]->alive == true)
							if(gPulse[hero]->active == false) {
								gPulse[hero]->posX = 10;
								gPulse[hero]->posY = 10;
							} else
								gPulse[hero]->posY += 6;
						if(gPulse[hero]->posY > 540)
							gPulse[hero]->active = false;
						if(gPulse[hero]->alive == false) {
							gPulse[hero]->posX = 10;
							gPulse[hero]->posY = 10;
							gPulse[hero]->alive = true;
						}
					for (int i = 0; i < rAmmo; i++) {
						if(rockets[i]->active == true)
							rockets[i]->posY -= 6;
						if(rockets[i]->posY < -10)
							rockets[i]->alive = false;
					}
					for (int i = 0; i < pAmmo; i++) {
						if(sPulse[i]->active == true)
							sPulse[i]->posY -= 10;
						if(sPulse[i]->posY < -10)
							sPulse[i]->alive = false;
					}
					if(beam->active == true)
						beam->posX = player->posX + 12;
					else
						beam->posX = -10;
					for(int i = 0; i < 3; i++)
						if(ship[i]->active == true)
							ship[i]->posX = player->posX;
					//render
					screen->render(this, 300, -540 + screenScroll);
					if(gPulse[hero]->alive == true)
						if(gPulse[hero]->active == true)
							gPulse[hero]->render(this, gPulse[hero]->posX, gPulse[hero]->posY);
					for (int i = 0; i < troops; i++)
						if(grunt[i]->alive == true)
							grunt[i]->render(this, grunt[i]->posX, grunt[i]->posY);
					edgeR->render(this);
					edgeL->render(this, 660);
					if(player->weapon == 0)
						for(int i = 0; i < rAmmo; i++)
							if(rockets[i]->alive == true)
								rockets[i]->render(this, rockets[i]->posX, rockets[i]->posY);
					if(player->weapon == 1)
						for(int i = 0; i < pAmmo; i++)
							if(sPulse[i]->alive == true)
								sPulse[i]->render(this, sPulse[i]->posX, sPulse[i]->posY);
					if(player->weapon == 2) {
						if(beam->active == true)
							beam->render(this, beam->posX, beam->posY);
						for(int i = 0; i < 10; i++)
							energy2[i]->render(this, 181 - (i * 9), 351);
						for(int i = 0; i < 10; i++)
							if(charge >= i + 1)
								energy[i]->render(this, 181 - (i * 9), 351);
					}
					for(int i = 0; i < 3; i++)
						if(ship[i]->alive == true)
							ship[i]->render(this, ship[i]->posX, ship[i]->posY);
					int board = score;
					for(int i = 0; i < 6; i++) {
						dig = 5 - i;
						scoreboard[(board % 10) + (dig * 10)]->render(this, 760 + (18 * dig), 106);		
						board /= 10;
					}
					xButton->render(this, 20, 20);
					if (muted == true)
						muteButton->render(this, 60, 20);
					else
						speakerButton->render(this, 60, 20);
					//increment
					step++;
					spawning++;
					respawn++;
					phase++;
					screenScroll++;
					if(screenScroll >= 540) //reset screen
						screenScroll = 0;
					//collision	
						//check player
					if(respawn > 30)
						for (int i = 0; i < 3; i++)
							if(ship[i]->active == true) {
								for (int j = 0; j < troops; j++)
									if(grunt[j]->alive == true)
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
								if(ship[i]->alive == false)
									if(gameOver > 1){
										player->alive = false;
										room = "over";
									}
								else
									for(int k = 0; k < 3; k++)
										if(ship[k]->alive == true) {
												respawn = 0;
												ship[i]->active = false;
												player->weapon = ship[k]->weapon;
												ship[i]->posX = temp->posX;
												ship[i]->posY = temp->posY;
												ship[k]->active = true;
												temp->posX = ship[k]->posX;
												temp->posY = ship[k]->posY;
												ship[k]->posY = player->posY;
												gameOver++;
												break;
										}
							}
						//check projectile
					for (int i = 0; i < rAmmo; i++)
						if(rockets[i]->alive == true)
							if(rockets[i]->active == true) {
								for (int j = 0; j < troops; j++)
									if(grunt[j]->alive == true)
										score += collision(rockets[i], grunt[j], collisionS);
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
										if(gPulse[j]->active == true)
											collision(gPulse[j], rockets[i], collisionS);
							}
					for (int i = 0; i < pAmmo; i++)
						if(sPulse[i]->alive == true)
							if(sPulse[i]->active == true) {
								for (int j = 0; j < troops; j++)
									if(grunt[j]->alive == true)
										score += collision(sPulse[i], grunt[j], collisionS);
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
										if(gPulse[j]->active == true)
											collision(gPulse[j], sPulse[i], collisionS);
							}
					if(beam->active == true)
						if(beam->active == true) {
							for (int j = 0; j < troops; j++) {
								beam->alive = true;
								if(grunt[j]->alive == true)
									score += collision(grunt[j], beam, collisionS);
							}
							for (int j = 0; j < troops; j++)
								if(gPulse[j]->alive == true)
									if(gPulse[j]->active == true)
										collision(gPulse[j], beam, collisionS);
				
						}
				} else if(room == "pause") {
					screen->render(this, 300, -540 + screenScroll);
					pauseButton->render(this, 423, 112);
					edgeR->render(this);
					edgeL->render(this, 660);
					int board = score;
					for(int i = 0; i < 6; i++) {
						dig = 5 - i;
						scoreboard[(board % 10) + (dig * 10)]->render(this, 760 + (18 * dig), 106);		
						board /= 10;
					}
					for(int i = 0; i < 3; i++)
						if(ship[i]->alive == true && ship[i]->active == false)
							ship[i]->render(this, ship[i]->posX, ship[i]->posY);
					if(player->weapon == 0)
						for(int i = 0; i < rAmmo; i++)
							if(rockets[i]->alive == true && rockets[i]->active == false)
								rockets[i]->render(this, rockets[i]->posX, rockets[i]->posY);
					if(player->weapon == 1)
						for(int i = 0; i < pAmmo; i++)
							if(sPulse[i]->alive == true && sPulse[i]->active == false)
								sPulse[i]->render(this, sPulse[i]->posX, sPulse[i]->posY);
					if(player->weapon == 2) {
						for(int i = 0; i < 10; i++)
							energy2[i]->render(this, 181 - (i * 9), 351);
						for(int i = 0; i < 10; i++)
							if(charge >= i + 1)
								energy[i]->render(this, 181 - (i * 9), 351);
					}
					xButton->render(this, 20, 20);
					if (muted == true)
						muteButton->render(this, 60, 20);
					else
						speakerButton->render(this, 60, 20);
				} else if(room == "over") {
					screen->render(this, 300, -540 + screenScroll);
					gameoverButton->render(this, 348, 143);
					edgeR->render(this);
					edgeL->render(this, 660);
					int board = score;
					for(int i = 0; i < 6; i++) {
						dig = 5 - i;
						scoreboard[(board % 10) + (dig * 10)]->render(this, 760 + (18 * dig), 106);		
						board /= 10;
					}
					xButton->render(this, 20, 20);
					if (muted == true)
						muteButton->render(this, 60, 20);
					else
						speakerButton->render(this, 60, 20);
				}
				SDL_RenderPresent(renderer);
				SDL_Delay(16);
			}
		}
		Mix_CloseAudio();
};

int  main(int argc, char* argv[]) {
	Game *SF;
	SF = new NewGame();
	SF->run();
	delete SF;
	return 0;
}
