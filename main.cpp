#include"SDL.h"
#include<iostream>
#include"world.h"
#include"input.h"

using std::cerr;
using std::endl;

SDL_Surface *screen;

const double FPS = 60;

void init();

int main(int argc, char **argv)
{
	init();
			
	input *i = new input();
	world *w = new world(screen, i);
	w->init();

	double prev = SDL_GetTicks();
	int frames = 0;

	SDL_Event e;
	bool quit(false);
	while(!quit)
	{
		i->reset_pressed();
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_KEYDOWN:
				i->handle_keydown(e.key.keysym);
				break;
			case SDL_KEYUP:
				i->handle_keyup(e.key.keysym);
				break;
			case SDL_QUIT:
				quit = true;
				break;
			default:
				break;
			}		
		}
		
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff)); 
		w->update();
		w->render();
		SDL_Flip(screen);
		
		// cap the frame rate
		double ticks = SDL_GetTicks();
		double delay = (1000/FPS) - (ticks - prev);
		prev = ticks;
		if (delay < FPS && delay > 0)
			SDL_Delay((Uint32)delay);
	}
	
	SDL_Quit();
	delete i;
	delete w;
	cerr << "Exiting" << endl;

	exit(0);
}


void init()
{
	cerr << "Initialising SDL" << endl;
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
	{
		cerr << "Could not initialise SDL! " << endl << SDL_GetError() << endl;
		exit(-1);
	}
	
	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

	if (screen == NULL)
	{
		cerr << "Failed to apply video settings!" << endl;
		cerr << SDL_GetError() << endl;
		exit(-1);
	}
}

