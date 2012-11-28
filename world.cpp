#include"world.h"
#include<sstream>
#include<iostream>

world::~world()
{
	delete m_background;
	delete p1;
	delete p2;
	delete m_ball;
}

void world::init() 
{
	load_backround("linux.bmp");
	init_ball();
	init_paddels();
}

void world::update(Uint32 time) 
{
	detect_collisions();
	p1->update(time);
	p2->update(time);
	m_ball->update(time);
}

void world::render() 
{
	SDL_BlitSurface(m_background,NULL,m_screen,NULL);
	std::string msg;
	std::stringstream ss;
	ss << "P1 Wins: " << m_p1_wins << "  P2 Wins: " << m_p2_wins;
	m_text_writer->draw_text(4,4, ss.str());
	p1->render();
	p2->render();
	m_ball->render();
}

void world::detect_collisions()
{
	if(m_ball->X() + m_ball->L() >= (m_screen->w - p2->W()))
	{
		if(m_ball->Y()+m_ball->L() >= p2->Y() && m_ball->Y() <= p2->Y() + p2->H())
		{
			m_ball->reverse_x();
			++m_collisions;
		}
	}
	else if(m_ball->X() <= p1->W())
	{
		if(m_ball->Y()+m_ball->L() >= p1->Y() && m_ball->Y() <= p1->Y() + p1->H())
		{
			m_ball->reverse_x();
			++m_collisions;
		}
	}

	if(m_ball->Y() >= m_screen->h || m_ball->Y() <= 0)
	{
		m_ball->reverse_y();
	}
	
	if ( m_ball->X() + m_ball->L() >= m_screen->w)
	{
		++m_p1_wins;
		reset_game();
	}
	else if(m_ball->X() <= 0)
	{
		++m_p2_wins;
		reset_game();
	}
}

void world::load_backround(const char *file)
{
	SDL_Surface *tmp;
	tmp = SDL_LoadBMP(file);
	m_background = SDL_DisplayFormat(tmp);

	if (m_background->format->palette && m_screen->format->palette) {
		SDL_SetColors(m_screen, m_background->format->palette->colors, 0,
			m_background->format->palette->ncolors);
	}

	SDL_FreeSurface(tmp);
}

void world::init_ball()
{
	Uint16 l = 10;
	Uint16 x = m_screen->w / 2 - l / 2;
	Uint16 y = m_screen->h / 2 - l / 2;
	m_ball = new ball(x, y, l, this);
}

void world::init_paddels()
{
	p1 = new paddel(0, m_screen->h/2 - 20, 7, 40, this);
	p1->bind_down(SDLK_s);
	p1->bind_up(SDLK_w);
	p2 = new paddel(m_screen->w-7, m_screen->h/2 - 20, 7, 40, this);
}

void world::reset_game()
{
	delete p1;
	delete p2;
	delete m_ball;
	m_collisions = 0;
	init_ball();
	init_paddels();
}
