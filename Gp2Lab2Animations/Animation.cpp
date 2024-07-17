#include "Animation.h"
#include "animation.h"
#include <iostream>
#include<fstream>
#include<sstream>
using namespace std;

Animation::Animation() :AnimationPlayed(false), surface(nullptr), texture(nullptr)
{
}

Animation::~Animation() {
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
void Animation::Initialize(SDL_Renderer* renderer)
{
	Initialize_Sprite(	SpriteSheetFile);
	surface = IMG_Load(spritesheet.ImageFile.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}
void Animation::Initialize_Sprite(const string& SpriteSheetFile)
{
	ifstream File;
	File.open(SpriteSheetFile);
	if (!File.is_open())return;

	getline(File, spritesheet.ImageFile);
	string Line;
	while (getline(File, Line))
	{
		stringstream sstream(Line);
		vector<string> words;
		string word;
		while (sstream >> word) words.push_back(word);
		if (words.size() != 4)continue;
		spritesheet.Sprites.push_back(
			Rect{stoi(words[0]),stoi(words[1]),stoi(words[2]),stoi(words[3]),});
	}
	File.close();
}

void Animation::LoadAnimation(const std::string& AnimationFile)
{
	ifstream File;
	File.open(AnimationFile);
	if (!File.is_open())return;

	getline(File, SpriteSheetFile);
	getline(File, AnimationType);
	if (AnimationType == "PingPong")
	{
		string Line;
		getline(File, Line);
		stringstream sstream(Line);
		int frame;
		while (sstream >> frame)PingPong.push_back(frame);
		for (int i = PingPong.size() - 1; i >= 0; i--)
		{
			PingPong.push_back(PingPong[i]);
		}
		File.close();

	}
	else if (AnimationType == "Looping")
	{
		string Line;
		getline(File, Line);
		stringstream sstream(Line);
		int frame;
		while (sstream >> frame)Looping.push_back(frame);
		File.close();
	}
	else if (AnimationType == "Once")
	{
		string Line;
		getline(File, Line);
		stringstream sstream(Line);
		int frame;
		while (sstream >> frame)Once.push_back(frame);
		File.close();
	}
}