#include"world.h"

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

void world::update() 
{
	detect_collisions();
	p1->update();
	p2->update();
	m_ball->update();
}

void world::render() 
{
	SDL_BlitSurface(m_background,NULL,m_screen,NULL);
	p1->render();
	p2->render();
	m_ball->render();
}

void world::detect_collisions()
{
	if(m_ball->X() + m_ball->L() >= (m_screen->w - p2->W()) || m_ball->X() <= p1->W())
	{
		if( (m_ball->Y()+m_ball->L() >= p1->Y() && m_ball->Y() <= p1->Y() + p1->H() ) ||
			(m_ball->Y()+m_ball->L() >= p2->Y() && m_ball->Y() <= p2->Y() + p2->H() ) )
			m_ball->reverse_x();
	}

	if(m_ball->Y() >= m_screen->h || m_ball->Y() <= 0)
	{
		m_ball->reverse_y();
	}

	if ( m_ball->X() + m_ball->L() > m_screen->w || m_ball->X() < 0)
		reset_game();
}

void world::load_backround(const char *file)
{
	SDL_Surface *tmp;
	tmp = SDL_LoadBMP(file);
	if (tmp == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\\n", file, SDL_GetError());
		return;
	}
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
	init_ball();
	init_paddels();
}