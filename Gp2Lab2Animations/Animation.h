#pragma once
#include <iostream>
#include<fstream>
#include "Sprite Sheet.h"
#include "SDL.h"
#include "SDL_image.h"
using namespace std;
struct Animation
{
	string File;
	string SpriteSheetFile;
	string AnimationType;
	SpriteSheet spritesheet;
	vector<int>Looping;
	vector<int>PingPong;
	vector<int>Once;
	SDL_Surface* surface;
	SDL_Texture* texture;
	bool AnimationPlayed;
	int AnimationFrames = 150;
	Animation();
	~Animation();
	void Initialize(SDL_Renderer* renderer);
	void	Initialize_Sprite(const string& SpriteSheetFile);
	void LoadAnimation(const string& AnimationFile);
};


