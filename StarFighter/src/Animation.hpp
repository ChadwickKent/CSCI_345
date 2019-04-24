#pragma once

#include "SDL.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Game.hpp"

using namespace std;

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
