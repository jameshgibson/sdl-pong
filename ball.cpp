#include"ball.h"
#include"world.h"

void ball::update()
{
	if(m_speed == 0 && m_world->Input()->is_keypressed(SDLK_RETURN)) inc_speed(2);
	move();
}

void ball::render()
{
	SDL_Rect r;
	r.x = m_x;
	r.y = m_y;
	r.h = r.w = m_diameter;
	Uint32 yellow = SDL_MapRGB(m_world->Surface()->format, 0xff, 0xff, 0x00);
	SDL_FillRect(m_world->Surface(),&r,yellow);
}

void ball::move()
{
	m_x += m_speed*m_direction[0];
	m_y += m_speed*m_direction[1];
}