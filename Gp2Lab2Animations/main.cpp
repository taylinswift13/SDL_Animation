
#include <iostream>
#include "SDL.h"
#include "Animation.h"
#include "SDL_image.h"
#include"Screen.h"

void renderAnimation(Animation& animation, Screen& screen, float time, string AnimationType, int destination) {

	SDL_Rect Source;
	int frameIndex = (int)(time / animation.AnimationFrames);
	int frameSize=0;
	if (AnimationType == "PingPong") { frameSize = ((int)animation.PingPong.size()); }
	else if (AnimationType == "Looping") { frameSize = ((int)animation.Looping.size()); }
	else if (AnimationType == "Once") { frameSize = ((int)animation.Once.size()); }
	int frameIndexLooping = frameIndex % frameSize;
	int frame = 0;
	if (AnimationType == "PingPong") { frame = animation.PingPong[frameIndexLooping]; }
	else if (AnimationType == "Looping") { frame = animation.Looping[frameIndexLooping]; }
	else if (AnimationType == "Once") { frame = animation.Once[frameIndexLooping]; }
	Source.x = animation.spritesheet.Sprites[frame].x;
	Source.y = animation.spritesheet.Sprites[frame].y;
	Source.h = animation.spritesheet.Sprites[frame].w;
	Source.w = animation.spritesheet.Sprites[frame].h;

	SDL_Rect Destination;
	Destination.x = destination;
	Destination.y = destination-100;
	Destination.w = Source.w * 4;
	Destination.h = Source.h * 4;

	float Seconds = ((float)time) / 1000.0f;
	Destination.x += (int)(cos(Seconds) * 30);
	Destination.y += (int)(sin(Seconds) * 30);
	SDL_RenderCopy(screen.renderer, animation.texture, &Source, &Destination);
	if (AnimationType == "Once") 
	{ 
		if (frame == animation.Once.back()) 
		{ animation.AnimationPlayed = true; } 
	}

}
int Initialize_sdl() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to Init SDL_Init, %s", SDL_GetError());
		return -1;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("Error IMG_Init: %s", IMG_GetError());
		return -2;
	}
	return 0;
}
int main(int argc, char* args[])
{
	Animation Animation_1, Animation_2, Animation_3;
	Animation_1.LoadAnimation("Looping.txt");
	Animation_2.LoadAnimation("Once.txt");
	Animation_3.LoadAnimation("PingPong.txt");
	Animation_1.Initialize_Sprite(Animation_1.SpriteSheetFile);
	Animation_2.Initialize_Sprite(Animation_2.SpriteSheetFile);
	Animation_3.Initialize_Sprite(Animation_3.SpriteSheetFile);
	Initialize_sdl();
	if (Initialize_sdl < 0)
	{
		return Initialize_sdl();
	}
	Screen screen;
	screen.Init(1000,600);
	Animation_1.Initialize(screen.renderer);
	Animation_2.Initialize(screen.renderer);
	Animation_3.Initialize(screen.renderer);
	const int framesPerSecond = 24;
	const int frameLength = 1000 / framesPerSecond;
	bool oneTimeAnimaOn = true;

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		auto time = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		// Render and update
		SDL_SetRenderDrawColor(screen.renderer, 255, 110, 0,255);
		SDL_RenderClear(screen.renderer);

		//looping

		if (!Animation_1.AnimationPlayed) { renderAnimation(Animation_1, screen, (float)time, Animation_1.AnimationType, 100); }

		//oneTimeAnima
		if (!Animation_2.AnimationPlayed) { renderAnimation(Animation_2, screen, (float)time, Animation_2.AnimationType, 250); }
		//pingpong
		if (!Animation_3.AnimationPlayed) { renderAnimation(Animation_3, screen, (float)time, Animation_3.AnimationType, 350); }


		SDL_RenderPresent(screen.renderer);


		int timeElapsed = SDL_GetTicks() - time;
		int timeToWait = frameLength - timeElapsed;

		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}
	}
	return 0;
}
