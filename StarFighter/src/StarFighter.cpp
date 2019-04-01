#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <sstream>
#include <time.h>
//include "Game.hpp"

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

class Image { // images are used for any static image (doesn't need to check for collision -chad)
	SDL_Texture *texture;
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
		void render(Game *game, int x = 0, int y = 0) {
			SDL_Rect dest;
			dest.w = src.w;
			dest.h = src.h;
			dest.x = x;
			dest.y = y;
			SDL_Renderer *renderer= game->getRenderer();
			SDL_RenderCopy(renderer, texture, &src, &dest);
		}
};

//typedef pair<Image *,int /*time */> frameWithTime;

/*class Animation { // haven't used yet -chad
	vector < frameWithTime > frames;
	int time, totalTime, frame;
	public:
	Animation(Game *game, string path, int count, int fps = 10) {
		stringstream filename;
		totalTime = 0;
		for (int i = 0;i < count; i++) {
			filename << path << setw(5) << setfill('0') << i << ".bmp";
			Image *img = new Image(game, filename.str());
			frames.push_back(frameWithTime(img, 1000 / fps));
			totalTime += 1000 / fps;
		}
		frame=0;
	}
	void update(float dt) {
		time += (int)dt;
		time = time % totalTime;
		int currentTime=time;
		for (int i = 0;i < frames.size();i++) {
			if (currentTime < frames[i].second) {
				frame = i;
				break;
			}
			currentTime -= frames[i].second;
		}
	}
	SDL_Rect getSize() {
		SDL_Rect neverHappen;
		if (frames.size()>0) return frames[frame].first->getSize();
		return neverHappen;
	}
	void render(Game *game, int x = 0,int y =0) {
		frames[frame].first->render(game, x, y);
	}
};*/

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

class NewGame:public Game {
	string file = "../include/";
	Image *background;
	Image *title;
	Image *playButton;
	Image *pauseButton;
	Image *gameoverButton;
	Image *edgeR;
	Image *edgeL;
	Image *screen;
	vector<Image *> scoreboard;
	vector<Image *> energy;
	vector<Image *> energy2;
	int digits = 60;
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
			background = new Image(this, file + "bgd.bmp");
			title = new Image(this, file + "title.bmp");
			playButton = new Image(this, file + "playButton.bmp");
			pauseButton = new Image(this, file + "pauseButton.bmp");
			gameoverButton = new Image(this, file + "gameoverButton.bmp");
			edgeR = new Image(this, file + "frameR.bmp");
			edgeL = new Image(this, file + "frameL.bmp");
			screen = new Image(this, file + "screen.bmp");
			int count = 0;
			for (int i = 0; i < digits; i++) {
				Image *digit = new Image(this, file + to_string(count) + ".bmp");
				scoreboard.push_back(digit);
				count++;
				if(count > 9)
					count = 0;
			}
			for (int i = 0; i < 10; i++) { // pulse weapon
				Image *e = new Image(this, file + "energy.bmp");
				energy.push_back(e);
			}
			for (int i = 0; i < 10; i++) { // pulse weapon
				Image *e2 = new Image(this, file + "energy2.bmp");
				energy2.push_back(e2);
			}
			player = new Sprite(this, file + "non0.bmp", 465, 440); // non0 is a empty texture to give a hit box (i want this to change -chad)
			temp = new Sprite(this, file + "non0.bmp", 0, 0);
			for (int i = 0; i < 3; i++) {
				Sprite *vehicle = new Sprite(this, file + "ship" + to_string(i + 1) + ".bmp", 78 + (47 * i), 401);
				ship.push_back(vehicle); 
			}
			for (int i = 0; i < 10; i++) { // rocket weapon
				Sprite *rocket = new Sprite(this, file + "rocket.bmp", 181 - (i * 9), 351);
				rockets.push_back(rocket);
			}
			for (int i = 0; i < 10; i++) { // pulse weapon
				Sprite *pulse2 = new Sprite(this, file + "pulse2.bmp", 181 - (i * 9), 351);
				sPulse.push_back(pulse2);
			}
			beam = new Sprite(this, file + "beam.bmp", -10, 0);
			for (int i = 0; i < troops; i++) {
				Sprite *enemy = new Sprite(this, file + "grunt.bmp", 325 + ((i * 40) - (320 * (i / 8))), 70 + (42 * (i / 8)));
				grunt.push_back(enemy);
			}
			for (int i = 0; i < troops; i++) {
				Sprite *pulse = new Sprite(this, file + "pulse.bmp", grunt[i]->posX, grunt[i]->posY);
				gPulse.push_back(pulse);
			}
		}
		void loop() {
			SDL_Event event;
			unsigned start = SDL_GetTicks();
			bool running = true;
			bool paused = false;
			string room = "title";
			string ph = "level";
			int step = 0;			//ticks
			int screenScroll = 0;
			int dir = 1;			//direction
			int score = 0;
			int respawn = 30;
			int charge = 10;
			int phase = 0;
			int spawning = 0;
			int dig = 0;			//digit
			int hero = 24;			//active enemy ship
			int gameOver = 0;
			
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
				if(SDL_PollEvent(&event))
					if(event.type == SDL_QUIT)
						running = false;
					if(event.type == SDL_KEYDOWN) {
						if(room == "title") //title screen
							if(event.key.keysym.sym == SDLK_RETURN) 
								room = "level";
						if(room == "over") //replay
							if(event.key.keysym.sym == SDLK_RETURN) {
								
								running = false;
							}
						if(event.key.keysym.sym == SDLK_ESCAPE) //quits
							running = false;
						if(room != "title")
							if(event.key.keysym.sym == SDLK_TAB && room != "title")	//pauses
								if(room != "over") {
									if(paused == false) {
										ph = room;
										paused = true;
										room = "pause";
									} else {
										paused = false;
										room = ph;
									}
								}
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
											}
								}
							if(player->weapon == 2)
								if(event.key.keysym.sym == SDLK_SPACE && charge > 9) {
									beam->posY = player->posY - 540;
									beam->active = true;
									charge = 0;
									phase = 0;
								}
							swap(event, SDLK_q, 0, ship, player, temp);
							swap(event, SDLK_w, 1, ship, player, temp);
							swap(event, SDLK_e, 2, ship, player, temp);
							if(event.key.keysym.sym == SDLK_k)//kill
								for(int i = 0; i < 3; i++)
									if(ship[i]->active == true)
										ship[i]->alive = false;
						}
					}
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if(room == "level") {
					if(currentKeyStates[SDL_SCANCODE_RIGHT])
						if(player->posX < 619)
							player->posX += 5;
					if(currentKeyStates[SDL_SCANCODE_LEFT])
						if(player->posX > 310)
							player->posX -= 5;
				}
				SDL_Renderer *renderer = getRenderer();
				if(room == "title") {
					background->render(this);
					title->render(this, 259, 112);
					playButton->render(this, 399, 300);
				} else if(room == "level") {
					if(!(step % 30)) //enemy drift
						dir *= -1;
					else if(!(step % 60))
						dir *= 1;
					if(!(step % 146)) { //active enemy event
						if(hero < 24) {
							if(hero == 0) //return
								grunt[hero]->posX = grunt[1]->posX - 40;
							else
								grunt[hero]->posX = grunt[0]->posX + ((hero * 40) - (320 * (hero / 8)));
							grunt[hero]->posY = 70 + (42 * (hero / 8));
						}
						if(spawning > 500) {
							cout << "working" << endl;
							for(int i = 0; i < 30; i++) {
								hero = rand() % 24; //new active enemy
								if(grunt[hero]->alive == true)
									break;
							}
						} else {
							hero = 24;
							cout << 24;
						}
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
								if(spawning < 100) {
									
									//325 + ((i * 40) - (320 * (i / 8))), 70 + (42 * (i / 8))
								} else {
									if(!(step % 3))
										grunt[i]->posX += 1 * dir;
								}
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
					for(int i = 0; i < 3; i++)
						if(ship[i]->alive == true)
							ship[i]->render(this, ship[i]->posX, ship[i]->posY);
					int board = score;
					for(int i = 0; i < 6; i++) {
						dig = 5 - i;
						scoreboard[(board % 10) + (dig * 10)]->render(this, 760 + (18 * dig), 106);		
						board /= 10;
					}
							
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
										collision(grunt[j], ship[i]);
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
										collision(gPulse[j], ship[i]);
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
										score += collision(rockets[i], grunt[j]);
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
										if(gPulse[j]->active == true)
											collision(gPulse[j], rockets[i]);
							}
					for (int i = 0; i < pAmmo; i++)
						if(sPulse[i]->alive == true)
							if(sPulse[i]->active == true) {
								for (int j = 0; j < troops; j++)
									if(grunt[j]->alive == true)
										score += collision(sPulse[i], grunt[j]);
								for (int j = 0; j < troops; j++)
									if(gPulse[j]->alive == true)
										if(gPulse[j]->active == true)
											collision(gPulse[j], sPulse[i]);
							}
					if(beam->active == true)
						if(beam->active == true) {
							for (int j = 0; j < troops; j++) {
								beam->alive = true;
								if(grunt[j]->alive == true)
									score += collision(grunt[j], beam);
							}
							for (int j = 0; j < troops; j++)
								if(gPulse[j]->alive == true)
									if(gPulse[j]->active == true)
										collision(gPulse[j], beam);
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
				}
				SDL_RenderPresent(renderer);
				SDL_Delay(16);
			}
		}
};
	
int  main(int argc, char* argv[]) {
	Game *SF;
	SF = new NewGame();
	SF->run();
	delete SF;
	return 0;
}
