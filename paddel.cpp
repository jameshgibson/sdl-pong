#include"paddel.h"
#include"world.h"

void paddel::update(Uint32 time)
{
	if(m_world->Input()->is_keydown(m_key_down))
	{
		if(m_y + m_height < m_world->Surface()->h) m_y += m_speed*(time);
	}
	if(m_world->Input()->is_keydown(m_key_up))
	{
		if(m_y > 0) m_y -= m_speed*(time);
	}
}

void paddel::render()
{
	SDL_Rect r;
	r.h = m_height;
	r.w = m_width;
	r.x = m_x;
	r.y = m_y;
	Uint32 red = SDL_MapRGB(m_world->Surface()->format, 0xff, 0x00, 0x00);
	SDL_FillRect(m_world->Surface(),&r,red);
}