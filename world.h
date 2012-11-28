#pragma once
#include<SDL.h>
#include"paddel.h"
#include"ball.h"
#include"input.h"
#include"text_writer.h"

class world
{
private:
	SDL_Surface *m_screen;
	SDL_Surface *m_background;
	paddel *p1;
	paddel *p2;
	ball *m_ball;
	input *m_input;
	text_writer *m_text_writer;

	Uint32 m_collisions;
	Uint32 m_p1_wins;
	Uint32 m_p2_wins;


public:
	world(SDL_Surface *screen, input *input, text_writer *tw) : m_screen(screen), 
		m_input(input), m_text_writer(tw), m_collisions(0), m_p1_wins(0), m_p2_wins(0)
	{}

	~world();

	void init();

	void update(Uint32 time);
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
