#include<SDL.h>
#include<iostream>
#include"world.h"
#include"input.h"
#include"text_writer.h"
#include<sstream>

using std::cerr;
using std::endl;

SDL_Surface *screen;

const double FPS = 60;

void init();

int main(int argc, char **argv)
{
  init();		
  input *i = new input();
  text_writer *tw = new text_writer(screen);
  world *w = new world(screen, i, tw);
  w->init();

  double prev = SDL_GetTicks();

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
      w->update(1);
      w->render();
      SDL_Flip(screen);

      double ticks = SDL_GetTicks();
      double elapsed_time = (ticks - prev);
      prev = ticks;
      double delay = (1000/FPS) - elapsed_time;
      if (delay >= 0)
	SDL_Delay((Uint32)delay);
    }

  SDL_Quit();
  delete i;
  cerr << "Exiting" << endl;

  exit(0);
}


void init()
{
  if(TTF_Init()==-1) 
    {
      cerr << "TTF_Init: " << TTF_GetError() << endl;
      exit(2);
    }

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
