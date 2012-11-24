#pragma once
#include<SDL.h>
#include"paddel.h"
#include"ball.h"
#include"input.h"

class world
{
private:
	SDL_Surface *m_screen;
	SDL_Surface *m_background;
	paddel *p1;
	paddel *p2;
	ball *m_ball;
	input *m_input;

public:
	world(SDL_Surface *screen, input *input) : m_screen(screen), 
		m_input(input)
	{}

	~world();

	void init();

	void update();
	void render();

	input * Input() { return m_input; }
	SDL_Surface * Surface() { return m_screen; }

private:
	void detect_collisions();
	void load_backround(const char *file);
	void init_ball();
	void init_paddels();
	void reset_game();
};
